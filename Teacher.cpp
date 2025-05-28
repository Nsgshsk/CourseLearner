#include "Teacher.h"

static int PREFIX = 2000;

void Teacher::generate_id()
{
    setId(PREFIX + count);
    count++;
}

Teacher::Teacher(const String& first_name, const String& last_name, const String& password) :
User(first_name, last_name, password)
{
    generate_id();
}
