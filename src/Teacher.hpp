#ifndef TEACHER_HPP
#define TEACHER_HPP

#include <vector>
#include "Person.hpp"
#include "Student.hpp" 

class Teacher : public Person {
private:
    std::vector<Student*> students; 

public:
    Teacher(int id, std::string name, std::string email, std::string password);

    void addStudent(Student* student);
    std::vector<Student*>& getStudents();
    void assignSubject(Student* student, Subject* subject);
    
    // Existing Add logic
    void recordAssessment(Student* student, std::string subjectName, Assessment a);

    // NEW: Update logic
    void updateAssessment(Student* student, std::string subjectName, int assessmentIndex, float score, float total, std::string feedback);

    void displayInfo() const override;
};

#endif // TEACHER_HPP