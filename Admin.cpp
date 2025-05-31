#include "Admin.h"

void Admin::generate_id()
{
    setId(0);
}

Admin::Admin(const String& first_name, const String& last_name, const String& password) :
User(first_name, last_name, password, ADMIN)
{
    generate_id();
}