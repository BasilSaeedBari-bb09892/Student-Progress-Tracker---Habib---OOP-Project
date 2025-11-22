#ifndef ASSESSMENT_HPP
#define ASSESSMENT_HPP

#include <string>
#include <iostream>

class Assessment {
private:
    std::string title;
    float score;
    float totalMarks;
    std::string feedback;
    std::string date;

public:
    Assessment(std::string t, float s, float tm, std::string f, std::string d);

    std::string getTitle() const;
    float getScore() const;
    float getTotalMarks() const;
    std::string getFeedback() const;
    std::string getDate() const;
    float getPercentage() const;

    // NEW: Setters for updating data
    void setScore(float s);
    void setTotalMarks(float tm);
    void setFeedback(const std::string& f);
};

#endif // ASSESSMENT_HPP