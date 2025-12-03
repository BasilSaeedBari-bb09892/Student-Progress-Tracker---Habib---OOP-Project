#include "Person.hpp"

Person::Person(int id,
     std::string name,
      std::string email,
       std::string password)
    : id(id), name(name), email(email), password(password) {}

int Person::getId() const { return id; }
std::string Person::getName() const { return name; }
std::string Person::getEmail() const { return email; }
std::string Person::getPassword() const { return password; }

void Person::setName(const std::string& n) { name = n; } //no extra copy, can use pointers to copy, 1 instead of 2
void Person::setEmail(const std::string& e) { email = e; }
void Person::setPassword(const std::string& p) { password = p; }