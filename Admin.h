#pragma once
#include "User.h"

class Admin final : public User
{
    void generate_id() override;
public:
    Admin(const String& first_name, const String& last_name, const String& password);
};
