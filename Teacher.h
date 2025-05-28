#pragma once
#include "User.h"

class Teacher final : public User
{
    static unsigned char count;
    void generate_id() override;
public:
    Teacher(const String& first_name, const String& last_name, const String& password);
};
