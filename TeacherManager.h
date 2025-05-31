#pragma once
#include "AppManager.h"
#include "User.h"

class TeacherManager
{
public:
    void login();
    TeacherManager(const User& user, const DataRepository& data);
};
