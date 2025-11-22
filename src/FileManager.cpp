#include "FileManager.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// Helper: Split string by delimiter
std::vector<std::string> FileManager::split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// =============================================================================
// SAVE LOGIC
// =============================================================================
void FileManager::saveAllData(const std::vector<Teacher*>& teachers, 
                              const std::vector<Student*>& students,
                              const std::vector<std::string>& globalSubjects) {
    try {
        fs::create_directories("data/students");
    } catch (const std::exception& e) {
        std::cerr << "Error creating directories: " << e.what() << std::endl;
        return;
    }

    saveSubjects(globalSubjects);
    saveTeachers(teachers);

    for (const auto& s : students) {
        saveSingleStudent(s);
    }
}

void FileManager::saveSubjects(const std::vector<std::string>& globalSubjects) {
    std::ofstream file("data/subjects.txt");
    if (!file.is_open()) return;
    for (const auto& sub : globalSubjects) {
        file << sub << "\n";
    }
}

void FileManager::saveTeachers(const std::vector<Teacher*>& teachers) {
    std::ofstream file("data/teachers.txt");
    if (!file.is_open()) return;
    for (const auto& t : teachers) {
        file << t->getId() << "|" << t->getName() << "|" << t->getEmail() << "|" << t->getPassword() << "\n";
    }
}

void FileManager::saveSingleStudent(Student* s) {
    std::string filename = "data/students/" + std::to_string(s->getId()) + ".txt";
    std::ofstream file(filename);
    if (!file.is_open()) return;

    file << "INFO|" << s->getId() << "|" << s->getName() << "|" << s->getEmail() << "|" << s->getPassword() << "\n";

    for (const auto& sub : s->getSubjects()) { 
        // UPDATED FORMAT: Include TeacherID and TeacherName
        file << "SUBJECT_START|" << sub->getName() << "|" << sub->getTargetGrade() 
             << "|" << sub->getTeacherId() << "|" << sub->getTeacherName() << "\n";
        
        for (const auto& a : sub->getAssessments()) {
            file << "ASSESSMENT|" << a.getTitle() << "|" << a.getScore() << "|" 
                 << a.getTotalMarks() << "|" << a.getFeedback() << "|" << a.getDate() << "\n";
        }
        file << "SUBJECT_END\n";
    }
}

// =============================================================================
// LOAD LOGIC
// =============================================================================
void FileManager::loadAllData(std::vector<Teacher*>& teachers, 
                              std::vector<Student*>& students,
                              std::vector<std::string>& globalSubjects) {
    
    if (!fs::exists("data")) return;

    loadSubjects(globalSubjects);
    loadTeachers(teachers);

    if (fs::exists("data/students")) {
        for (const auto& entry : fs::directory_iterator("data/students")) {
            if (entry.path().extension() == ".txt") {
                Student* s = loadSingleStudent(entry.path());
                if (s) {
                    students.push_back(s);
                    // Link student to ALL teachers (Logic: Teachers see all students, filter subjects later)
                    for(auto* t : teachers) {
                        t->addStudent(s);
                    }
                }
            }
        }
    }
}

void FileManager::loadSubjects(std::vector<std::string>& globalSubjects) {
    std::ifstream file("data/subjects.txt");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) globalSubjects.push_back(line);
    }
}

void FileManager::loadTeachers(std::vector<Teacher*>& teachers) {
    std::ifstream file("data/teachers.txt");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto parts = split(line, '|');
        if (parts.size() >= 4) {
            try {
                teachers.push_back(new Teacher(std::stoi(parts[0]), parts[1], parts[2], parts[3]));
            } catch (...) {}
        }
    }
}

Student* FileManager::loadSingleStudent(const fs::path& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) return nullptr;

    std::string line;
    Student* student = nullptr;
    Subject* currentSubject = nullptr;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto parts = split(line, '|');
        if (parts.empty()) continue;

        std::string type = parts[0];
        
        try {
            if (type == "INFO" && parts.size() >= 5) {
                student = new Student(std::stoi(parts[1]), parts[2], parts[3], parts[4]);
            }
            else if (student && type == "SUBJECT_START" && parts.size() >= 5) {
                // PARSE NEW FORMAT: Name|Target|TeacherID|TeacherName
                float target = 100.0f;
                int tId = 0;
                std::string tName = "Unknown";
                
                try { 
                    target = std::stof(parts[2]); 
                    tId = std::stoi(parts[3]);
                    tName = parts[4];
                } catch(...) {}
                
                Subject* sub = new Subject(parts[1], target, tId, tName);
                student->addSubject(sub);
                currentSubject = sub;
            }
            // Backwards compatibility for old files (Optional safety)
            else if (student && type == "SUBJECT_START" && parts.size() >= 3) {
                float target = 100.0f;
                try { target = std::stof(parts[2]); } catch(...) {}
                // Default to Admin if old format
                Subject* sub = new Subject(parts[1], target, 1, "Admin");
                student->addSubject(sub);
                currentSubject = sub;
            }
            else if (currentSubject && type == "ASSESSMENT" && parts.size() >= 6) {
                float score = 0.0f, total = 100.0f;
                try { score = std::stof(parts[2]); total = std::stof(parts[3]); } catch(...) {}
                
                Assessment a(parts[1], score, total, parts[4], parts[5]);
                currentSubject->addAssessment(a);
            }
            else if (type == "SUBJECT_END") {
                currentSubject = nullptr;
            }
        } catch (...) {}
    }
    return student;
}