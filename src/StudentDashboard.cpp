#include "StudentDashboard.hpp"
#include "App.hpp"
#include <iomanip>
#include <sstream>

StudentDashboard::StudentDashboard(Student* student) : currentStudent(student) {
    window = new Fl_Double_Window(800, 600, "Student Dashboard");
    
    // 1. Header Group
    Fl_Group* header = new Fl_Group(0, 0, 800, 80);
    header->box(FL_FLAT_BOX);
    header->color(fl_rgb_color(80, 50, 140)); 
    
    std::string welcome = "Welcome, " + student->getName();
    welcomeBox = new Fl_Box(20, 20, 300, 40);
    welcomeBox->copy_label(welcome.c_str());
    welcomeBox->labelcolor(FL_WHITE);
    welcomeBox->labelsize(20);
    welcomeBox->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
    
    std::stringstream ss;
    ss << "Avg: " << std::fixed << std::setprecision(1) << student->calculateAverage() << "%";
    gpaBox = new Fl_Box(650, 20, 100, 40);
    gpaBox->copy_label(ss.str().c_str());
    gpaBox->labelcolor(FL_WHITE);
    gpaBox->labelsize(20);
    
    header->end(); 
    
    // 2. Subject Tabs (Created BEFORE the button so they are 'behind' it)
    subjectTabs = new Fl_Tabs(20, 100, 760, 430);
    
    if (student->getSubjects().empty()) {
        Fl_Group* noData = new Fl_Group(20, 130, 760, 400, "No Data");
        new Fl_Box(20, 130, 760, 400, "No subjects assigned yet.");
        noData->end();
    } else {
        for (Subject* sub : student->getSubjects()) {
            createSubjectTab(sub, 20, 130, 760, 400);
        }
    }
    subjectTabs->end();

    // 3. Logout Button (Moved to end to ensure it is Top-Most / Clickable)
    Fl_Button* logoutBtn = new Fl_Button(700, 550, 80, 30, "Logout");
    logoutBtn->callback(logout_cb);

    window->end();
}

StudentDashboard::~StudentDashboard() { delete window; }
void StudentDashboard::show() { window->show(); }
void StudentDashboard::logout_cb(Fl_Widget* w, void* v) { App::instance->logout(); }

void StudentDashboard::createSubjectTab(Subject* sub, int x, int y, int w, int h) {
    Fl_Group* tab = new Fl_Group(x, y, w, h);
    
    // VISUAL UPDATE: Show "Subject Name (Teacher Name)"
    std::string label = sub->getName() + "\n(" + sub->getTeacherName() + ")";
    tab->copy_label(label.c_str());
    
    Fl_Chart* chart = new Fl_Chart(x + 20, y + 20, w - 300, h - 40, "Progress");
    chart->type(FL_BAR_CHART);
    
    Fl_Browser* feedList = new Fl_Browser(x + w - 260, y + 40, 240, h - 60, "Feedback");
    
    for (const auto& a : sub->getAssessments()) {
        std::string lbl = a.getTitle();
        Fl_Color col = (a.getPercentage() >= 80) ? FL_GREEN : (a.getPercentage() >= 50 ? FL_YELLOW : FL_RED);
        chart->add(a.getPercentage(), strdup(lbl.c_str()), col);
        
        std::string f = "@b" + a.getTitle() + ": " + a.getFeedback();
        feedList->add(f.c_str());
    }
    tab->end();
}