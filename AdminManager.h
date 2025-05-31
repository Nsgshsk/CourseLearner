#pragma once
#include "AppManager.h"
#include "User.h"

class AdminManager
{
public:
    void login();
    AdminManager(const User& user, const DataRepository& data);
};
