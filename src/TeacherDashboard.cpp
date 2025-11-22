#include "TeacherDashboard.hpp"
#include "App.hpp"
#include <FL/fl_ask.H>
#include <FL/Fl_Secret_Input.H>
#include <string>
#include <cstdlib> 
#include <vector>

float safe_float(const char* val) {
    if (!val || *val == 0) return 0.0f;
    try { return std::stof(val); } catch (...) { return 0.0f; }
}

TeacherDashboard::TeacherDashboard(Teacher* teacher) : currentTeacher(teacher) {
    window = new Fl_Double_Window(1000, 600, "Teacher Dashboard");
    
    sidebar = new Fl_Group(0, 0, 200, 600);
    Fl_Box* box = new Fl_Box(0, 0, 200, 600);
    box->box(FL_FLAT_BOX);
    box->color(fl_rgb_color(50, 50, 50)); 
    
    addStudentBtn = new Fl_Button(20, 40, 160, 35, "@+ Add Student");
    addStudentBtn->callback(add_student_click_cb, this);
    addStudentBtn->color(fl_rgb_color(80, 120, 80)); 
    addStudentBtn->labelcolor(FL_WHITE);

    addSubjectBtn = new Fl_Button(20, 85, 160, 35, "@+ Create Subject");
    addSubjectBtn->callback(add_subject_click_cb, this);
    addSubjectBtn->color(fl_rgb_color(80, 100, 140)); 
    addSubjectBtn->labelcolor(FL_WHITE);

    logoutBtn = new Fl_Button(20, 550, 160, 30, "Logout");
    logoutBtn->callback(logout_cb);
    sidebar->end();

    mainArea = new Fl_Group(200, 0, 800, 600);
    
    std::string welcome = "Welcome, " + teacher->getName();
    Fl_Box* header = new Fl_Box(220, 20, 500, 40);
    header->copy_label(welcome.c_str());
    header->labelsize(20);
    header->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);

    Fl_Box* lbl1 = new Fl_Box(220, 80, 200, 20, "Select Student:");
    lbl1->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    
    studentList = new Fl_Hold_Browser(220, 110, 250, 400);
    studentList->callback(student_select_cb, this);
    fillStudentList();

    Fl_Group* formGroup = new Fl_Group(500, 110, 450, 400);
    formGroup->box(FL_BORDER_BOX);
    
    selectedStudentName = new Fl_Box(520, 120, 400, 30, "No Student Selected");
    selectedStudentName->labelfont(FL_BOLD);
    
    subjectChoice = new Fl_Choice(600, 170, 200, 30, "Subject:");
    subjectChoice->callback(subject_change_cb, this);
    
    assessmentChoice = new Fl_Choice(600, 220, 200, 30, "Assessment:");
    assessmentChoice->callback(assessment_change_cb, this);
    assessmentChoice->add("Create New...");
    assessmentChoice->value(0);

    assessmentTitleInput = new Fl_Input(600, 270, 200, 30, "New Title:");
    scoreInput = new Fl_Float_Input(600, 320, 80, 30, "Score:");
    totalInput = new Fl_Float_Input(720, 320, 80, 30, "/ Total:");
    feedbackInput = new Fl_Input(600, 370, 200, 30, "Feedback:");
    
    actionBtn = new Fl_Button(600, 420, 200, 30, "Add Assessment");
    actionBtn->callback(action_cb, this);
    actionBtn->color(fl_rgb_color(80, 50, 140));
    actionBtn->labelcolor(FL_WHITE);
    
    formGroup->end();
    mainArea->end();
    
    window->end();

    refreshSubjectList(); 
}

TeacherDashboard::~TeacherDashboard() { delete window; }
void TeacherDashboard::show() { window->show(); }

void TeacherDashboard::fillStudentList() {
    studentList->clear();
    for (Student* s : currentTeacher->getStudents()) {
        std::string label = s->getName() + " (" + s->getEmail() + ")";
        studentList->add(label.c_str(), s); 
    }
}

void TeacherDashboard::refreshSubjectList() {
    subjectChoice->clear();
    const auto& subs = App::instance->getGlobalSubjects();
    for (const auto& s : subs) {
        subjectChoice->add(s.c_str());
    }
    if (!subs.empty()) {
        subjectChoice->value(0);
        refreshAssessmentList();
    }
}

void TeacherDashboard::refreshAssessmentList() {
    assessmentChoice->clear();
    assessmentChoice->add("Create New...");
    assessmentChoice->value(0);
    if(!assessmentTitleInput) return;

    assessmentTitleInput->value(""); assessmentTitleInput->activate();
    scoreInput->value(""); totalInput->value(""); feedbackInput->value("");
    actionBtn->copy_label("Add Assessment");

    int line = studentList->value();
    if (line == 0) return;
    Student* s = (Student*)studentList->data(line);

    int subIdx = subjectChoice->value();
    if (subIdx < 0) return;
    std::string subName = subjectChoice->text(subIdx);

    // CRITICAL UPDATE: Only show assessments that match MY Teacher ID
    for (auto* subj : s->getSubjects()) {
        if (subj->getName() == subName && subj->getTeacherId() == currentTeacher->getId()) {
            for (const auto& a : subj->getAssessments()) {
                assessmentChoice->add(a.getTitle().c_str());
            }
            break;
        }
    }
}

void TeacherDashboard::logout_cb(Fl_Widget* w, void* v) { App::instance->logout(); }

void TeacherDashboard::student_select_cb(Fl_Widget* w, void* v) {
    TeacherDashboard* d = (TeacherDashboard*)v;
    int line = d->studentList->value();
    if (line == 0) return;
    Student* s = (Student*)d->studentList->data(line);
    d->selectedStudentName->copy_label(s->getName().c_str());
    d->refreshAssessmentList();
}
void TeacherDashboard::subject_change_cb(Fl_Widget* w, void* v) { ((TeacherDashboard*)v)->refreshAssessmentList(); }

void TeacherDashboard::assessment_change_cb(Fl_Widget* w, void* v) {
    TeacherDashboard* d = (TeacherDashboard*)v;
    int choice = d->assessmentChoice->value();

    if (choice == 0) {
        d->assessmentTitleInput->activate(); d->assessmentTitleInput->value("");
        d->scoreInput->value(""); d->totalInput->value(""); d->feedbackInput->value("");
        d->actionBtn->copy_label("Add Assessment");
    } else {
        int vecIdx = choice - 1;
        int line = d->studentList->value();
        Student* s = (Student*)d->studentList->data(line);
        std::string subName = d->subjectChoice->text(d->subjectChoice->value());

        // FILTER BY TEACHER ID
        for (auto* subj : s->getSubjects()) {
            if (subj->getName() == subName && subj->getTeacherId() == d->currentTeacher->getId()) {
                const auto& assessments = subj->getAssessments();
                if (vecIdx < assessments.size()) {
                    const Assessment& a = assessments[vecIdx];
                    d->assessmentTitleInput->value(a.getTitle().c_str());
                    d->assessmentTitleInput->deactivate();
                    d->scoreInput->value(std::to_string((int)a.getScore()).c_str());
                    d->totalInput->value(std::to_string((int)a.getTotalMarks()).c_str());
                    d->feedbackInput->value(a.getFeedback().c_str());
                    d->actionBtn->copy_label("Update Marks");
                }
                break;
            }
        }
    }
}

void TeacherDashboard::action_cb(Fl_Widget* w, void* v) {
    TeacherDashboard* d = (TeacherDashboard*)v;
    int line = d->studentList->value();
    if (line == 0) { fl_alert("Select Student!"); return; }
    int subIdx = d->subjectChoice->value();
    if (subIdx < 0) { fl_alert("Select Subject!"); return; }
    
    Student* s = (Student*)d->studentList->data(line);
    std::string sub = d->subjectChoice->text(subIdx);
    
    float scr = safe_float(d->scoreInput->value());
    float tot = safe_float(d->totalInput->value());
    std::string fdb = d->feedbackInput->value();

    int choice = d->assessmentChoice->value();
    if (choice == 0) {
        std::string tit = d->assessmentTitleInput->value();
        if (tit.empty()) { fl_alert("Title required!"); return; }
        Assessment a(tit, scr, tot, fdb, "2025-11-22");
        d->currentTeacher->recordAssessment(s, sub, a); // Logic handles Teacher ID internally
        fl_message("Added!");
    } else {
        int vecIdx = choice - 1;
        d->currentTeacher->updateAssessment(s, sub, vecIdx, scr, tot, fdb); // Logic handles Teacher ID internally
        fl_message("Updated!");
    }
    d->refreshAssessmentList();
}

struct StudentCreationData { Fl_Input* name; Fl_Input* email; Fl_Input* pass; Fl_Window* popup; TeacherDashboard* dash; };
void TeacherDashboard::add_student_click_cb(Fl_Widget* w, void* v) {
    TeacherDashboard* d = (TeacherDashboard*)v;
    Fl_Window* p = new Fl_Window(300, 250, "Add Student"); p->set_modal();
    Fl_Input* n = new Fl_Input(100,30,180,30,"Name:");
    Fl_Input* e = new Fl_Input(100,80,180,30,"Email:");
    Fl_Secret_Input* ps = new Fl_Secret_Input(100,130,180,30,"Pass:");
    Fl_Button* b = new Fl_Button(100,190,100,30,"Create");
    StudentCreationData* dt = new StudentCreationData{n,e,ps,p,d};
    b->callback(save_new_student_cb, dt);
    p->end(); p->show();
}
void TeacherDashboard::save_new_student_cb(Fl_Widget* w, void* v) {
    StudentCreationData* d = (StudentCreationData*)v;
    if(strlen(d->name->value())==0) return;
    int id = 2000+rand()%9000;
    App::instance->registerStudent(new Student(id, d->name->value(), d->email->value(), d->pass->value()));
    d->dash->fillStudentList(); d->popup->hide(); delete d->popup; delete d;
}

struct SubjectCreationData { Fl_Input* name; Fl_Window* popup; TeacherDashboard* dash; };
void TeacherDashboard::add_subject_click_cb(Fl_Widget* w, void* v) {
    TeacherDashboard* d = (TeacherDashboard*)v;
    Fl_Window* p = new Fl_Window(300, 150, "New Subject"); p->set_modal();
    Fl_Input* n = new Fl_Input(100, 40, 180, 30, "Name:");
    Fl_Button* b = new Fl_Button(100, 90, 100, 30, "Add");
    SubjectCreationData* dt = new SubjectCreationData{n,p,d};
    b->callback(save_new_subject_cb, dt);
    p->end(); p->show();
}
void TeacherDashboard::save_new_subject_cb(Fl_Widget* w, void* v) {
    SubjectCreationData* d = (SubjectCreationData*)v;
    if(strlen(d->name->value())>0) {
        App::instance->addGlobalSubject(d->name->value());
        d->dash->refreshSubjectList();
    }
    d->popup->hide(); delete d->popup; delete d;
}