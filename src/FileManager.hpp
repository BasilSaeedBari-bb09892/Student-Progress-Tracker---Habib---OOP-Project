#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <vector>
#include <string>
#include <filesystem> // C++17 Standard for folder handling
#include "Teacher.hpp"
#include "Student.hpp"

class FileManager {
public:
    static void saveAllData(const std::vector<Teacher*>& teachers, 
                            const std::vector<Student*>& students,
                            const std::vector<std::string>& globalSubjects);

    static void loadAllData(std::vector<Teacher*>& teachers, 
                            std::vector<Student*>& students,
                            std::vector<std::string>& globalSubjects);

private:
    static std::vector<std::string> split(const std::string &s, char delimiter);
    
    // Helpers to keep the main logic clean
    static void saveTeachers(const std::vector<Teacher*>& teachers);
    static void saveSubjects(const std::vector<std::string>& globalSubjects);
    static void saveSingleStudent(Student* s);
    
    static void loadTeachers(std::vector<Teacher*>& teachers);
    static void loadSubjects(std::vector<std::string>& globalSubjects);
    static Student* loadSingleStudent(const std::filesystem::path& filePath);
};

#endif // FILEMANAGER_HPP