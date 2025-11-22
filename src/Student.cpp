#include "Student.hpp"
#include <iostream>

Student::Student(int id, std::string name, std::string email, std::string password)
    : Person(id, name, email, password), averagePerformance(0.0f) {}

Student::~Student() {
    // Composition: Student owns Subjects, so we must delete them
    for (Subject* s : subjects) {
        delete s;
    }
    subjects.clear();
}

void Student::addSubject(Subject* s) {
    subjects.push_back(s);
}

std::vector<Subject*>& Student::getSubjects() {
    return subjects;
}

float Student::calculateAverage() {
    if (subjects.empty()) {
        averagePerformance = 0.0f;
        return 0.0f;
    }
    
    float total = 0.0f;
    for (Subject* s : subjects) {
        total += s->calculateAverage();
    }
    averagePerformance = total / subjects.size();
    return averagePerformance;
}

void Student::displayInfo() const {
    std::cout << "Student: " << name << " (ID: " << id << ")" << std::endl;
}

void Student::loadDataFromFile() {
    // Delegated to FileManager in this architecture
}
void Student::saveDataToFile() {
    // Delegated to FileManager in this architecture
}