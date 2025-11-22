#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <vector>
#include "Person.hpp"
#include "Subject.hpp"

class Student : public Person {
private:
    std::vector<Subject*> subjects; // Composition: Student owns Subjects
    float averagePerformance;

public:
    // Constructor
    Student(int id, std::string name, std::string email, std::string password);
    
    // Destructor (Must delete subjects)
    ~Student();

    // Core Logic
    void addSubject(Subject* s);
    float calculateAverage(); // Updates and returns averagePerformance
    std::vector<Subject*>& getSubjects(); // Mutable access for Teacher to add assessments

    // Overrides
    void displayInfo() const override;
    
    // File IO Helpers (Internal use)
    void loadDataFromFile();
    void saveDataToFile();
};

#endif // STUDENT_HPP