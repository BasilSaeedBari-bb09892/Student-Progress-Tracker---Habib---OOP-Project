#include "Subject.hpp"
#include <numeric>
#include <sstream>
#include <iomanip>

// Updated Constructor to accept Teacher Context
Subject::Subject(std::string n, float target, int tId, std::string tName) 
    : name(n), targetGrade(target), teacherId(tId), teacherName(tName) {}

void Subject::addAssessment(const Assessment& a) {
    assessments.push_back(a);
}

std::string Subject::getName() const { return name; }
float Subject::getTargetGrade() const { return targetGrade; }
const std::vector<Assessment>& Subject::getAssessments() const { return assessments; }
int Subject::getTeacherId() const { return teacherId; }
std::string Subject::getTeacherName() const { return teacherName; }

float Subject::calculateAverage() const {
    if (assessments.empty()) return 0.0f;
    float totalPercent = 0.0f;
    for (const auto& a : assessments) {
        totalPercent += a.getPercentage();
    }
    return totalPercent / assessments.size();
}

std::string Subject::generateSummary() const {
    std::stringstream ss;
    ss << "Subject: " << name << " (" << teacherName << ") | Avg: " << std::fixed << std::setprecision(2) << calculateAverage() << "%";
    return ss.str();
}

Assessment* Subject::getAssessmentInternal(int index) {
    if (index >= 0 && index < assessments.size()) {
        return &assessments[index];
    }
    return nullptr;
}