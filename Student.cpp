#include "Student.h"

static constexpr int PREFIX = 1000;

void Student::generate_id()
{
    setId(PREFIX + rand() % PREFIX);
}

Student::Student(const String& first_name, const String& last_name, const String& password) :
User(first_name, last_name, password, STUDENT)
{
    generate_id();
}
