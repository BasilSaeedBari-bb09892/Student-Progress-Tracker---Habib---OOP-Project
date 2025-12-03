#ifndef TEACHERDASHBOARD_HPP
#define TEACHERDASHBOARD_HPP
// 1. Add includes
#include "TeacherReport.hpp" 
#include "FileManager.hpp"
#include <FL/fl_ask.H>


#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Hold_Browser.H> 
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Choice.H> 

#include "Teacher.hpp"

class TeacherDashboard {
private:
    Teacher* currentTeacher;
    Fl_Double_Window *window;
    
    // Layout Components
    Fl_Group *sidebar;
    Fl_Group *mainArea;
    
    Fl_Button *logoutBtn;

    
    Fl_Button *addStudentBtn;
    Fl_Button *addSubjectBtn; 

    Fl_Hold_Browser *studentList;
    
    Fl_Box *selectedStudentName;
    
    // Dropdowns
    Fl_Choice *subjectChoice; 
    Fl_Choice *assessmentChoice; // NEW: To select New vs Existing
    
    Fl_Input *assessmentTitleInput;
    Fl_Float_Input *scoreInput;
    Fl_Float_Input *totalInput;
    Fl_Input *feedbackInput;
    Fl_Button *actionBtn; // Renamed from addAssessmentBtn because it can now Update

    // Callbacks
    static void full_data_report_cb(Fl_Widget* w, void* v); // NEW Callback
    static void class_report_cb(Fl_Widget* w, void* v);
    static void logout_cb(Fl_Widget* w, void* v);
    static void action_cb(Fl_Widget* w, void* v); // Renamed
    static void student_select_cb(Fl_Widget* w, void* v);
    static void subject_change_cb(Fl_Widget* w, void* v); // NEW
    static void assessment_change_cb(Fl_Widget* w, void* v); // NEW
    
    static void add_student_click_cb(Fl_Widget* w, void* v);
    static void save_new_student_cb(Fl_Widget* w, void* v);
    static void add_subject_click_cb(Fl_Widget* w, void* v);
    static void save_new_subject_cb(Fl_Widget* w, void* v);
    
    void fillStudentList();
    void refreshSubjectList(); 
    void refreshAssessmentList(); // NEW Helper

public:
    TeacherDashboard(Teacher* teacher);
    ~TeacherDashboard();
    void show();
};

#endif // TEACHERDASHBOARD_HPP