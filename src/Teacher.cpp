#include "Teacher.hpp"

Teacher::Teacher(int id, std::string name, std::string email, std::string password)
    : Person(id, name, email, password) {}

void Teacher::addStudent(Student* student) {
    // Avoid duplicates in the local list
    for(auto* s : students) {
        if(s->getId() == student->getId()) return;
    }
    students.push_back(student);
}

std::vector<Student*>& Teacher::getStudents() {
    return students;
}

void Teacher::assignSubject(Student* student, Subject* subject) {
    if (student) {
        student->addSubject(subject);
    }
}

void Teacher::recordAssessment(Student* student, std::string subjectName, Assessment a) {
    if (!student) return;
    
    // Search for a subject that matches Name AND My Teacher ID
    for (Subject* s : student->getSubjects()) {
        if (s->getName() == subjectName && s->getTeacherId() == this->id) {
            s->addAssessment(a);
            return;
        }
    }
    
    // FIX: Pass 'this->id' and 'this->name' to the new constructor
    // This ensures the subject is "owned" by this specific teacher.
    Subject* newSub = new Subject(subjectName, 100.0f, this->id, this->name); 
    newSub->addAssessment(a);
    student->addSubject(newSub);
}

void Teacher::updateAssessment(Student* student, std::string subjectName, int assessmentIndex, float score, float total, std::string feedback) {
    if (!student) return;
    
    // Search for MY specific subject instance
    for (Subject* s : student->getSubjects()) {
        if (s->getName() == subjectName && s->getTeacherId() == this->id) {
            Assessment* a = s->getAssessmentInternal(assessmentIndex);
            if (a) {
                a->setScore(score);
                a->setTotalMarks(total);
                a->setFeedback(feedback);
            }
            return;
        }
    }
}

void Teacher::displayInfo() const {
    std::cout << "Teacher: " << name << " | Students: " << students.size() << std::endl;
}