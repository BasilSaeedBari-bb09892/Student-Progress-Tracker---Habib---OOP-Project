#include "Assessment.hpp"

Assessment::Assessment(std::string t, float s, float tm, std::string f, std::string d)
    : title(t), score(s), totalMarks(tm), feedback(f), date(d) {}

std::string Assessment::getTitle() const { return title; }
float Assessment::getScore() const { return score; }
float Assessment::getTotalMarks() const { return totalMarks; }
std::string Assessment::getFeedback() const { return feedback; }
std::string Assessment::getDate() const { return date; }

float Assessment::getPercentage() const {
    if (totalMarks == 0) return 0.0f;
    return (score / totalMarks) * 100.0f;
}

// NEW: Implementation of setters
void Assessment::setScore(float s) { score = s; }
void Assessment::setTotalMarks(float tm) { totalMarks = tm; }
void Assessment::setFeedback(const std::string& f) { feedback = f; }