#pragma once
#include "BaseManager.h"

class StudentManager : public BaseManager
{
    void enroll(const String& course, const String& password) const;
    void submit_assignment(const String& course, const String& assignment, const String& message) const;
    void grades() const;
    
public:
    StudentManager(User* user, DataRepository* data);
    void enroll_input() const;
    void submit_assignment_input() const;
    void login() override;
};
