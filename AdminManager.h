#pragma once
#include "BaseManager.h"

class AdminManager : public BaseManager
{
    void add_teacher(const String& first_name, const String& last_name);
    void add_teacher(const String& first_name, const String& last_name, const String& password);
    void add_student(const String& first_name, const String& last_name);
    void add_student(const String& first_name, const String& last_name, const String& password);
    void delete_user(int user_id);
    void delete_course(const String& course);
    void message_all(const String& message);
    void view_mailbox(int user_id);
    
    void add_teacher_input();
    void add_student_input();
    void delete_user_input();
    void delete_course_input();
    void message_all_input();
    void view_mailbox_input();
    
public:
    AdminManager(User* user, DataRepository* data);
    void login() override;
};
