#ifndef TEACHERREPORT_HPP
#define TEACHERREPORT_HPP

#include <string>
#include <map>
#include <vector>
#include "Teacher.hpp"

class TeacherReport {
public:
    // Existing Summary Report
    static std::string generate(Teacher* teacher);

    // NEW: Detailed Report (All students, all assignments)
    static std::string generateDetailedReport(Teacher* teacher);

private:
    static std::map<std::string, std::vector<std::pair<std::string, Subject*>>> 
    groupDataByCourse(Teacher* teacher);
};

#endif // TEACHERREPORT_HPP