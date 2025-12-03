#include "StudentDashboard.hpp"
#include "App.hpp"
#include "StudentReport.hpp" // Required for report logic
#include "FileManager.hpp"   // Required for saving files
#include <FL/fl_ask.H>       // Required for popups
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
    
    // Initial placeholder - this will be updated immediately by the tab logic
    gpaBox = new Fl_Box(600, 20, 150, 40);
    gpaBox->copy_label("Avg: --");
    gpaBox->labelcolor(FL_WHITE);
    gpaBox->labelsize(20);
    
    header->end(); 
    
    // 2. Subject Tabs
    subjectTabs = new Fl_Tabs(20, 100, 760, 430);
    
    // TRIGGER: Call tab_changed_cb whenever the user clicks a different tab
    subjectTabs->callback(tab_changed_cb, this); 
    
    if (student->getSubjects().empty()) {
        Fl_Group* noData = new Fl_Group(20, 130, 760, 400, "No Data");
        new Fl_Box(20, 130, 760, 400, "No subjects assigned yet.");
        noData->end();
    } else {
        for (Subject* sub : student->getSubjects()) { //
            createSubjectTab(sub, 20, 130, 760, 400);
        }
    }
    subjectTabs->end();

    // 3. Buttons
    Fl_Button* reportBtn = new Fl_Button(600, 550, 100, 30, "Get Report");
    reportBtn->callback(report_cb, currentStudent); 

    Fl_Button* logoutBtn = new Fl_Button(710, 550, 80, 30, "Logout");
    logoutBtn->callback(logout_cb);

    // 4. FORCE INITIAL UPDATE
    // Manually trigger the update for the first tab so the header isn't empty on load
    if (subjectTabs->children() > 0) {
        Fl_Widget* firstTab = subjectTabs->child(0);
        subjectTabs->value(firstTab); 
        updateHeaderStats((Subject*)firstTab->user_data());
    }

    window->end();
}

StudentDashboard::~StudentDashboard() { delete window; }
void StudentDashboard::show() { window->show(); }

void StudentDashboard::logout_cb(Fl_Widget* w, void* v) { 
    App::instance->logout(); 
}

void StudentDashboard::report_cb(Fl_Widget* w, void* v) {
    Student* s = (Student*)v;
    
    // Generate the report string using the new logic
    std::string report = StudentReport::generate(s); //
    
    std::string filename = s->getName() + "_Report.txt";
    
    // Save it
    FileManager::exportReport(filename, report); //
    
    fl_message("Report generated successfully!\nSaved to 'data/reports/%s'", filename.c_str());
}

void StudentDashboard::createSubjectTab(Subject* sub, int x, int y, int w, int h) {
    Fl_Group* tab = new Fl_Group(x, y, w, h);
    
    // CRITICAL: Store the Subject pointer inside the UI widget
    tab->user_data(sub); 
    
    // Visual Label: "Math (Mr. Smith)"
    std::string label = sub->getName() + "\n(" + sub->getTeacherName() + ")";
    tab->copy_label(label.c_str());
    
    Fl_Chart* chart = new Fl_Chart(x + 20, y + 20, w - 300, h - 40, "Progress");
    chart->type(FL_BAR_CHART);
    
    Fl_Browser* feedList = new Fl_Browser(x + w - 260, y + 40, 240, h - 60, "Feedback");
    
    for (const auto& a : sub->getAssessments()) { //
        std::string lbl = a.getTitle();
        Fl_Color col = (a.getPercentage() >= 80) ? FL_GREEN : (a.getPercentage() >= 50 ? FL_YELLOW : FL_RED);
        chart->add(a.getPercentage(), strdup(lbl.c_str()), col);
        
        std::string f = "@b" + a.getTitle() + ": " + a.getFeedback();
        feedList->add(f.c_str());
    }
    tab->end();
}

void StudentDashboard::tab_changed_cb(Fl_Widget* w, void* v) {
    StudentDashboard* dash = (StudentDashboard*)v;
    Fl_Tabs* tabs = (Fl_Tabs*)w;
    
    // Get the currently visible tab
    Fl_Widget* activeTab = tabs->value();
    
    if (activeTab) {
        // Retrieve the Subject pointer we stored in user_data
        Subject* sub = (Subject*)activeTab->user_data();
        
        // Update the header
        dash->updateHeaderStats(sub);
    }
}

void StudentDashboard::updateHeaderStats(Subject* sub) {
    if (!sub) return;
    
    std::stringstream ss;
    // Calculate average ONLY for this specific subject
    ss << "Sub Avg: " << std::fixed << std::setprecision(1) << sub->calculateAverage() << "%"; //
    
    // Update the existing GPA box
    gpaBox->copy_label(ss.str().c_str());
}