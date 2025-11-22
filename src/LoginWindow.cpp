#include "LoginWindow.hpp"
#include "App.hpp" 
#include <FL/fl_ask.H>

LoginWindow::LoginWindow(std::vector<Teacher*>& t, std::vector<Student*>& s)
    : teachers(t), students(s) 
{
    window = new Fl_Window(400, 500, "Student Progress Tracker");
    window->color(FL_WHITE);

    // Title
    titleBox = new Fl_Box(0, 50, 400, 50, "STUDENT TRACKER");
    titleBox->labelsize(24);
    titleBox->labelfont(FL_BOLD);
    titleBox->labelcolor(fl_rgb_color(80, 50, 140)); // Purple

    // Inputs
    emailInput = new Fl_Input(100, 150, 200, 30, "Email:");
    passwordInput = new Fl_Secret_Input(100, 200, 200, 30, "Password:");

    // Role Selection
    Fl_Group* roleGroup = new Fl_Group(100, 250, 200, 30);
    teacherRadio = new Fl_Round_Button(100, 250, 90, 30, "Teacher");
    teacherRadio->type(FL_RADIO_BUTTON);
    teacherRadio->value(1); // Default
    
    studentRadio = new Fl_Round_Button(210, 250, 90, 30, "Student");
    studentRadio->type(FL_RADIO_BUTTON);
    roleGroup->end();

    // Login Button
    loginButton = new Fl_Button(100, 320, 200, 40, "LOGIN");
    loginButton->color(fl_rgb_color(80, 50, 140));
    loginButton->labelcolor(FL_WHITE);
    loginButton->callback(login_cb, this);

    window->end();
}

void LoginWindow::show() { window->show(); }
void LoginWindow::hide() { window->hide(); }

void LoginWindow::login_cb(Fl_Widget* w, void* v) {
    ((LoginWindow*)v)->processLogin();
}

void LoginWindow::processLogin() {
    std::string email = emailInput->value();
    std::string pass = passwordInput->value();
    bool isTeacher = teacherRadio->value();

    if (isTeacher) {
        for (Teacher* t : teachers) {
            if (t->getEmail() == email && t->getPassword() == pass) {
                App::instance->showTeacherDashboard(t);
                return;
            }
        }
    } else {
        for (Student* s : students) {
            if (s->getEmail() == email && s->getPassword() == pass) {
                App::instance->showStudentDashboard(s);
                return;
            }
        }
    }
    
    fl_alert("Invalid Credentials!");
}