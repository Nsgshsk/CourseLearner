#include "Student.h"

static constexpr int PREFIX = 1000;

namespace 
{
    int strValue(const String& str)
    {
        const char* tmp = str.c_str();
        int result = 0;
        while (*tmp)
        {
            result += *tmp;
            tmp++;
        }
        return result;
    }
}

void Student::generate_id()
{
    setId(PREFIX + strValue(getFullName()) % PREFIX);
}

Student::Student(const String& first_name, const String& last_name, const String& password) :
User(first_name, last_name, password, STUDENT)
{
    generate_id();
}
