#include "StudentReport.hpp"
#include <sstream>
#include <iomanip>

std::string StudentReport::generate(Student* student) {
    if (!student) return "Error: No student data provided.";

    std::stringstream ss;
    ss << "==========================================\n";
    ss << "         STUDENT PROGRESS REPORT          \n";
    ss << "==========================================\n";
    ss << "Student Name: " << student->getName() << "\n"; //
    ss << "Student ID:   " << student->getId() << "\n";   //
    ss << "Email:        " << student->getEmail() << "\n";
    
    // Calculate overall average safely (Student::calculateAverage is not const in your code)
    float overallAvg = student->calculateAverage(); //
    ss << "Overall GPA:  " << std::fixed << std::setprecision(2) << overallAvg << "%\n";
    ss << "------------------------------------------\n\n";

    if (student->getSubjects().empty()) { //
        ss << "  [No subjects currently enrolled]\n";
    } else {
        for (Subject* sub : student->getSubjects()) {
            ss << generateSubjectSummary(sub);
        }
    }
    
    ss << "\n==========================================\n";
    ss << "Generated on: " << __DATE__ << " " << __TIME__ << "\n";
    return ss.str();
}

std::string StudentReport::generateSubjectSummary(Subject* subject) {
    if (!subject) return "";

    std::stringstream ss;
    ss << "SUBJECT: " << subject->getName() << "\n"; //
    ss << "  Instructor:   " << subject->getTeacherName() << "\n"; //
    ss << "  Target Grade: " << subject->getTargetGrade() << "%\n";
    ss << "  Current Avg:  " << subject->calculateAverage() << "%\n"; //
    
    ss << "  Assessments:\n";
    const auto& assessments = subject->getAssessments(); //
    
    if (assessments.empty()) {
        ss << "    [No assessments recorded]\n";
    } else {
        for (const auto& a : assessments) {
            ss << "    - " << std::left << std::setw(20) << a.getTitle() 
               << ": " << a.getScore() << "/" << a.getTotalMarks() 
               << " (" << std::fixed << std::setprecision(1) << a.getPercentage() << "%)\n";
        }
    }
    ss << "------------------------------------------\n";
    return ss.str();
}