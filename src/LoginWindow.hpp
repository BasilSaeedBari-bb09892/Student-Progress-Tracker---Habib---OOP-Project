#ifndef LOGINWINDOW_HPP
#define LOGINWINDOW_HPP

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Group.H>
#include <vector>

#include "Teacher.hpp"
#include "Student.hpp"

class LoginWindow {
private:
    Fl_Window *window;
    Fl_Input *emailInput;
    Fl_Secret_Input *passwordInput;
    Fl_Round_Button *teacherRadio;
    Fl_Round_Button *studentRadio;
    Fl_Button *loginButton;
    Fl_Box *titleBox;

    // Pointers to global data (passed from main)
    std::vector<Teacher*>& teachers;
    std::vector<Student*>& students;

    // Callback wrapper
    static void login_cb(Fl_Widget* w, void* v);
    void processLogin();

public:
    LoginWindow(std::vector<Teacher*>& t, std::vector<Student*>& s);
    void show();
    void hide();
};

#endif // LOGINWINDOW_HPP