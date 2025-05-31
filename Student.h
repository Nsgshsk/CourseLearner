#pragma once
#include "User.h"

class Student final : public User
{
    static unsigned char count;
    void generate_id() override;
public:
    Student(const String& first_name, const String& last_name, const String& password);

    static void setCount(unsigned char new_count);
};
