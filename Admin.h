#pragma once
#include "User.h"

class Admin final : public User
{
    static unsigned char count;
    void generate_id() override;
public:
    Admin(const String& first_name, const String& last_name, const String& password);

    static void setCount(unsigned char new_count);
};
