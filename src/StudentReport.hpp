#ifndef STUDENTREPORT_HPP
#define STUDENTREPORT_HPP

#include <string>
#include "Student.hpp"

class StudentReport {
public:
    // Generates a complete string report for a single student
    static std::string generate(Student* student);
    
    // Optional: Generates a specific report for just one subject
    static std::string generateSubjectSummary(Subject* subject);
};

#endif // STUDENTREPORT_HPP