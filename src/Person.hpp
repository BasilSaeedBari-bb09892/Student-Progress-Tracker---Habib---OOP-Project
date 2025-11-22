#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <iostream>

class Person {
protected:
    std::string name;
    std::string email;
    std::string password; // Added based on Login GUI requirements
    int id;

public:
    // Constructor
    Person(int id, std::string name, std::string email, std::string password);
    virtual ~Person() {} // Virtual destructor for proper cleanup

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPassword() const;

    // Setters
    void setName(const std::string& n);
    void setEmail(const std::string& e);
    void setPassword(const std::string& p);

    // Pure Virtual Method (Polymorphism)
    virtual void displayInfo() const = 0; 
};

#endif // PERSON_HPP