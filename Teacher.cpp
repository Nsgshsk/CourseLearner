#include "Teacher.h"
#include <ctime>

static constexpr int PREFIX = 2000;

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

void Teacher::generate_id()
{
    setId(PREFIX + strValue(getFullName()) % PREFIX);
}

Teacher::Teacher(const String& first_name, const String& last_name, const String& password) :
User(first_name, last_name, password, TEACHER)
{
    generate_id();
}