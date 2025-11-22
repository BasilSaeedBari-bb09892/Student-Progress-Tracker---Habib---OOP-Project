#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <string>
#include <vector>
#include "Assessment.hpp"

class Subject {
private:
    std::string name;
    std::vector<Assessment> assessments; 
    float targetGrade;
    
    // NEW: Ownership context
    int teacherId;
    std::string teacherName;

public:
    // Updated Constructor
    Subject(std::string n, float target, int tId, std::string tName);

    void addAssessment(const Assessment& a);
    
    std::string getName() const;
    float getTargetGrade() const;
    const std::vector<Assessment>& getAssessments() const;
    float calculateAverage() const;
    std::string generateSummary() const;

    // NEW Getters
    int getTeacherId() const;
    std::string getTeacherName() const;

    Assessment* getAssessmentInternal(int index);
};

#endif // SUBJECT_HPP