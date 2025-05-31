#include "Teacher.h"
#include <ctime>

static constexpr int PREFIX = 2000;

void Teacher::generate_id()
{
    setId(PREFIX + rand() % PREFIX);
}

Teacher::Teacher(const String& first_name, const String& last_name, const String& password) :
User(first_name, last_name, password, TEACHER)
{
    generate_id();
}