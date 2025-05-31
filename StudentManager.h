#pragma once
#include "AppManager.h"
#include "User.h"

class StudentManager
{
    User* user_;
    DataRepository* data_;

    void mailbox();
    void clear_mailbox();
    void enroll(const String& course, const String& password);
    void submit_assignment(const String& course, const String& assignment, const String& message);
    void message(int user_id, const String& message);
    void grades();
    
public:
    StudentManager(User& user, DataRepository& data);
    void login();
};
