#include "Admin.h"

void Admin::generate_id()
{
    setId(count);
    count++;
}

Admin::Admin(const String& first_name, const String& last_name, const String& password) :
User(first_name, last_name, password)
{
    generate_id();
}

void Admin::setCount(unsigned char new_count)
{
    count = new_count;
}