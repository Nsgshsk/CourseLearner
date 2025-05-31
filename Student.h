#pragma once
#include "User.h"

class Student final : public User
{
    void generate_id() override;
public:
    Student(const String& first_name, const String& last_name, const String& password);
};
