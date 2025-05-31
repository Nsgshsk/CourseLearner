#pragma once
#include "SerializableList.hpp"

class User;
class Course;
class String;

class DataRepository
{
    SerializableList<User> users_;
    SerializableList<Course> courses_;
public:
    const User& getUser(int id) const;
    User& getUser(int id);
    const Course& getCourse(const String& name) const;
    Course& getCourse(const String& name);

    const List<User>& getUsers() const;
    List<User>& getUsers();
    
    void addUser(const User& user);
    void addCourse(const Course& course);

    void removeUser(const User& user);
    void removeCourse(const Course& course);

    void clearUsers();
    void clearCourses();

    void saveData() const;
    void loadData();

    void saveDataDebug() const;
    void loadDataDebug();
};
