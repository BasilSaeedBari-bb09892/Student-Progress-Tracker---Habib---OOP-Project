#include "TeacherReport.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>

// ==========================================
// 1. SUMMARY REPORT GENERATOR
// ==========================================
std::string TeacherReport::generate(Teacher* teacher) {
    if (!teacher) return "Error: No teacher data provided.";

    std::stringstream ss;
    ss << "==========================================\n";
    ss << "         INSTRUCTOR CLASS REPORT          \n";
    ss << "==========================================\n";
    ss << "Instructor: " << teacher->getName() << "\n";
    ss << "ID:         " << teacher->getId() << "\n";
    ss << "==========================================\n\n";

    auto courseMap = groupDataByCourse(teacher);

    if (courseMap.empty()) {
        ss << "  [No active courses or students found]\n";
    }

    for (const auto& entry : courseMap) {
        std::string subjectName = entry.first;
        auto studentList = entry.second;

        ss << "COURSE: " << subjectName << "\n";
        ss << "Enrolled Students: " << studentList.size() << "\n";
        ss << "------------------------------------------\n";
        ss << std::left << std::setw(25) << "Student Name" 
           << std::setw(15) << "Average" 
           << "Status\n";
        ss << "------------------------------------------\n";

        float classTotal = 0.0f;
        int activeStudents = 0;

        for (const auto& pair : studentList) {
            std::string sName = pair.first;
            Subject* sub = pair.second;
            float avg = sub->calculateAverage();

            classTotal += avg;
            activeStudents++;

            std::string status = (avg >= sub->getTargetGrade()) ? "On Track" : "At Risk";

            ss << std::left << std::setw(25) << sName 
               << std::fixed << std::setprecision(1) << avg << "%          " 
               << status << "\n";
        }
        
        float classAvg = (activeStudents > 0) ? (classTotal / activeStudents) : 0.0f;
        ss << "------------------------------------------\n";
        ss << "CLASS AVERAGE: " << std::fixed << std::setprecision(1) << classAvg << "%\n\n";
    }

    ss << "==========================================\n";
    return ss.str();
}

// ==========================================
// 2. DETAILED REPORT GENERATOR (NEW)
// ==========================================
std::string TeacherReport::generateDetailedReport(Teacher* teacher) {
    if (!teacher) return "Error: No teacher data.";

    std::stringstream ss;
    ss << "=================================================\n";
    ss << "       DETAILED STUDENT PERFORMANCE LEDGER       \n";
    ss << "=================================================\n";
    ss << "Instructor: " << teacher->getName() << "\n";
    ss << "Report Date: " << __DATE__ << "\n";
    ss << "=================================================\n\n";

    bool anyDataFound = false;

    // Iterate through all students assigned to this teacher
    for (Student* s : teacher->getStudents()) {
        
        std::stringstream subSS;
        bool hasClassesWithTeacher = false;

        for (Subject* sub : s->getSubjects()) {
            // SECURITY CHECK: Only show subjects taught by THIS teacher
            if (sub->getTeacherId() == teacher->getId()) {
                hasClassesWithTeacher = true;
                anyDataFound = true;

                subSS << "  SUBJECT: " << sub->getName() << "\n";
                subSS << "  Current Average: " << std::fixed << std::setprecision(1) << sub->calculateAverage() << "%\n";
                subSS << "  Assessments:\n";

                const auto& assessments = sub->getAssessments();
                if (assessments.empty()) {
                    subSS << "    [No assessments recorded]\n";
                } else {
                    for (const auto& a : assessments) {
                         subSS << "    - " << std::left << std::setw(25) << a.getTitle() 
                               << " | Score: " << std::setw(5) << a.getScore() 
                               << " / " << std::setw(5) << a.getTotalMarks()
                               << " | " << a.getPercentage() << "%\n";
                    }
                }
                subSS << "  ---------------------------------------------\n";
            }
        }

        if (hasClassesWithTeacher) {
            ss << "STUDENT: " << s->getName() << " (ID: " << s->getId() << ")\n";
            ss << "Email: " << s->getEmail() << "\n";
            ss << "-------------------------------------------------\n";
            ss << subSS.str(); 
            ss << "\n";
        }
    }

    if (!anyDataFound) {
        ss << "No active student records found for your classes.\n";
    }

    ss << "================ END OF REPORT ==================\n";
    return ss.str();
}

// ==========================================
// 3. HELPER FUNCTION
// ==========================================
std::map<std::string, std::vector<std::pair<std::string, Subject*>>> 
TeacherReport::groupDataByCourse(Teacher* teacher) {
    std::map<std::string, std::vector<std::pair<std::string, Subject*>>> groups;
    int teacherId = teacher->getId();

    for (Student* s : teacher->getStudents()) {
        for (Subject* sub : s->getSubjects()) {
            if (sub->getTeacherId() == teacherId) {
                groups[sub->getName()].push_back({s->getName(), sub});
            }
        }
    }
    return groups;
}