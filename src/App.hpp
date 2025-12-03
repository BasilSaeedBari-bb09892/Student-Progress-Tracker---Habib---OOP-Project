#ifndef APP_HPP
#define APP_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <FL/Fl.H>

#include "Person.hpp"
#include "Teacher.hpp"
#include "Student.hpp"
#include "FileManager.hpp"

#include "LoginWindow.hpp"
#include "TeacherDashboard.hpp"
#include "StudentDashboard.hpp"

class App {
private:
    std::vector<Teacher*> teachers; //vectors to allow dynamic prog to avoid copying, to allow dynamic allocation, no limit, less space, direct mod 
    // (avoids copying large objects, allows polymorphism, create objects on the heap and manage them centrally.)
    std::vector<Student*> students;
    
    // NEW: Global list of subject names (e.g., "Math", "Science")
    std::vector<std::string> globalSubjects; 

    LoginWindow* loginWindow; //an object of created class "LoginWindow"
    TeacherDashboard* teacherDash;
    StudentDashboard* studentDash;

public:
    App() : loginWindow(nullptr), teacherDash(nullptr), studentDash(nullptr) {
        loadData();
        setupLogin();
    }

    ~App() {
        FileManager::saveAllData(teachers, students, globalSubjects);
        if (loginWindow) delete loginWindow;
        if (teacherDash) delete teacherDash;
        if (studentDash) delete studentDash;
        for (auto t : teachers) delete t;
        for (auto s : students) delete s;
        teachers.clear();
        students.clear();
    }

    void loadData() {
        FileManager::loadAllData(teachers, students, globalSubjects);
        if (teachers.empty()) {
            Teacher* defaultTeacher = new Teacher(1, "Admin Teacher", "admin@school.com", "password");
            teachers.push_back(defaultTeacher);
            // Default subjects if none exist
            if (globalSubjects.empty()) {
                globalSubjects.push_back("Mathematics");
                globalSubjects.push_back("English");
                globalSubjects.push_back("Science");
            }
            FileManager::saveAllData(teachers, students, globalSubjects);
        }
    }

    void setupLogin() {
        loginWindow = new LoginWindow(teachers, students);
    }

 
    // NEW: Subject Management

    void addGlobalSubject(std::string name) {
        // Avoid duplicates
        for (const auto& s : globalSubjects) {
            if (s == name) return;
        }
        globalSubjects.push_back(name);
        FileManager::saveAllData(teachers, students, globalSubjects);
    }

    const std::vector<std::string>& getGlobalSubjects() const {
        return globalSubjects;
    }

    // Student Registration
    void registerStudent(Student* s) {
        students.push_back(s);
        for(auto* t : teachers) {
            t->addStudent(s);
        }
        FileManager::saveAllData(teachers, students, globalSubjects);
    }

    // Navigation
    void showTeacherDashboard(Teacher* t) {
        if (loginWindow) loginWindow->hide();
        if (teacherDash) delete teacherDash; 
        teacherDash = new TeacherDashboard(t); 
        teacherDash->show();
    }

    void showStudentDashboard(Student* s) {
        if (loginWindow) loginWindow->hide();
        if (studentDash) delete studentDash;
        studentDash = new StudentDashboard(s);
        studentDash->show();
    }

    void logout() {
        if (teacherDash) {
            FileManager::saveAllData(teachers, students, globalSubjects);
            delete teacherDash;
            teacherDash = nullptr;
        }
        if (studentDash) {
            delete studentDash;
            studentDash = nullptr;
        }
        if (loginWindow) loginWindow->show();
    }

    int run() {
        if (loginWindow) loginWindow->show();
        return Fl::run();
    }
    
    static App* instance;
};

#endif // APP_HPP