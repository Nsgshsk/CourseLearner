#include "DataRepository.h"

#include "User.h"
#include "Course.h"

constexpr char USER_FILE[] = "users.bin";
constexpr char COURSE_FILE[] = "course.bin";

constexpr char USER_FILE_DEBUG[] = "users.debug.txt";
constexpr char COURSE_FILE_DEBUG[] = "course.debug.txt";

const User& DataRepository::getUser(int id) const
{
    for (size_t i = 0; i < users_.getSize(); i++)
        if (users_[i].getId() == id)
            return users_[i];

    throw std::out_of_range("Couldn't find user");
}

User& DataRepository::getUser(int id)
{
    for (size_t i = 0; i < users_.getSize(); i++)
        if (users_[i].getId() == id)
            return users_[i];

    throw std::out_of_range("Couldn't find user");
}

Course& DataRepository::getCourse(const String& name)
{
    for (size_t i = 0; i < courses_.getSize(); i++)
        if (courses_[i].getName() == name)
            return courses_[i];
    
    throw std::out_of_range("Couldn't find course");
}

const List<User>& DataRepository::getUsers() const
{
    return users_;
}

List<User>& DataRepository::getUsers()
{
    return users_;
}

const Course& DataRepository::getCourse(const String& name) const
{
    for (size_t i = 0; i < courses_.getSize(); i++)
        if (courses_[i].getName() == name)
            return courses_[i];
    
    throw std::out_of_range("Couldn't find course");
}

void DataRepository::addUser(const User& user)
{
    users_.add(user);
}

void DataRepository::addCourse(const Course& course)
{
    courses_.add(course);
}

void DataRepository::removeUser(const User& user)
{
    for (size_t i = 0; i < users_.getSize(); i++)
        if (users_[i] == user)
        {
            users_.removeAt(i);
            return;
        }

    throw std::out_of_range("Couldn't find user");
}

void DataRepository::removeCourse(const Course& course)
{
    for (size_t i = 0; i < courses_.getSize(); i++)
        if (courses_[i] == course)
        {
            courses_.removeAt(i);
            return;
        }
    
    throw std::out_of_range("Couldn't find course");
}

void DataRepository::clearUsers()
{
    users_.clear();
}

void DataRepository::clearCourses()
{
    courses_.clear();
}

void DataRepository::saveData() const
{
    std::ofstream user_file(USER_FILE, std::ios::binary);
    if (!user_file.is_open())
        throw std::runtime_error("Could not open file for writing");
    
    users_.serialize(user_file);

    user_file.close();

    std::ofstream course_file(COURSE_FILE, std::ios::binary);
    if (!course_file.is_open())
        throw std::runtime_error("Could not open file for writing");
    
    courses_.serialize(course_file);

    course_file.close();
}

void DataRepository::loadData()
{
    std::ifstream user_file(USER_FILE, std::ios::binary);
    if (!user_file.is_open())
        throw std::runtime_error("Could not open file for reading");
    
    users_.deserialize(user_file);

    user_file.close();

    std::ifstream course_file(COURSE_FILE, std::ios::binary);
    if (!course_file.is_open())
        throw std::runtime_error("Could not open file for reading");
    
    courses_.deserialize(course_file);

    course_file.close();
}

void DataRepository::saveDataDebug() const
{
    std::ofstream user_file(USER_FILE_DEBUG, std::ios::out | std::ios::beg);
    if (!user_file.is_open())
        throw std::runtime_error("Could not open file for writing");
    
    users_.serialize_debug(user_file);

    user_file.close();

    std::ofstream course_file(COURSE_FILE_DEBUG, std::ios::out | std::ios::beg);
    if (!course_file.is_open())
        throw std::runtime_error("Could not open file for writing");
    
    courses_.serialize_debug(course_file);

    course_file.close();
}

void DataRepository::loadDataDebug()
{
    std::ifstream user_file(USER_FILE_DEBUG, std::ios::out | std::ios::beg);
    if (!user_file.is_open())
        throw std::runtime_error("Could not open file for reading");
    
    users_.deserialize_debug(user_file);

    user_file.close();

    std::ifstream course_file(COURSE_FILE_DEBUG, std::ios::out | std::ios::beg);
    if (!course_file.is_open())
        throw std::runtime_error("Could not open file for reading");
    
    courses_.deserialize_debug(course_file);

    course_file.close();
}
