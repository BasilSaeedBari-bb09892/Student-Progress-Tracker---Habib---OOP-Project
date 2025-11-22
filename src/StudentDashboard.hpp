#ifndef STUDENTDASHBOARD_HPP
#define STUDENTDASHBOARD_HPP

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Chart.H> // For graphs
#include <FL/Fl_Text_Display.H> // For feedback
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

#include "Student.hpp"

class StudentDashboard {
private:
    Student* currentStudent;
    Fl_Double_Window *window;
    
    // Header
    Fl_Box *welcomeBox;
    Fl_Box *gpaBox;
    
    // Tabs for Subjects
    Fl_Tabs *subjectTabs;
    
    // Helper to build a tab for a specific subject
    void createSubjectTab(Subject* sub, int x, int y, int w, int h);

    static void logout_cb(Fl_Widget* w, void* v);

public:
    StudentDashboard(Student* student);
    ~StudentDashboard();
    void show();
};

#endif // STUDENTDASHBOARD_HPP