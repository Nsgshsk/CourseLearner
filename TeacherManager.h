#pragma once
#include "BaseManager.h"

class TeacherManager : public BaseManager
{
    void create_course(const String& course) const;
    void create_course(const String& course, const String& password) const;
    void set_course_password(const String& course, const String& password) const;
    void add_to_course(const String& course, int user_id) const;
    void assign_homework(const String& course, const String& title) const;
    void grade_homework(const String& course, const String& title, int user_id, double grade, const String& message) const;
    void message_students(const String& course, const String& message) const;

    void create_course_input() const;
    void add_to_course_input() const;
    void assign_homework_input() const;
    void grade_homework_input() const;
    void message_students_input() const;
    void set_course_password_input() const;
    
public:
    TeacherManager(User* user, DataRepository* data);
    void login() override;
};
