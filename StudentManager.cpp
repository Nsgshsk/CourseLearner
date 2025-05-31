#include "StudentManager.h"

#include <string>

#include "Course.h"

namespace
{
    constexpr uint8_t BUFFER_SIZE = 255;
    char Buffer[BUFFER_SIZE + 1];
}

void StudentManager::mailbox()
{
    for (size_t i = 0; i < user_->getInboxSize(); i++)
        std::cout << (*user_)[i];
}

void StudentManager::clear_mailbox()
{
    user_->clearMessages();
}

void StudentManager::enroll(const String& course, const String& password)
{
    try
    {
        Course& temp = data_->getCourse(course);
        temp.enroll(user_->getId(), password);
        user_->addCourse(course);
        std::cout << "Successfully enrolled into " << course << "!\n";
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void StudentManager::submit_assignment(const String& course, const String& assignment, const String& message)
{
    try
    {
        Course& temp = data_->getCourse(course);
        if (!temp.isUserEnrolled(user_->getId()))
            throw std::invalid_argument("User has not enrolled in the course!");

        temp.submitAssignment(assignment, message, user_->getId());
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void StudentManager::message(int user_id, const String& message)
{
    try
    {
        User& temp = data_->getUser(user_id);
        temp.addMessage(Message(user_->getFullName(), message));
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void StudentManager::grades()
{
    try
    {
        const List<String>& courses = user_->getCourses();
        for (size_t i = 0; i < courses.getSize(); i++)
        {
            Course& temp = data_->getCourse(courses[i]);
            List<Submission> assignments = temp.getUserAssignments(user_->getId());
            for (size_t j = 0; j < assignments.getSize(); j++)
                std::cout << courses[i] << " | " << assignments[j] << '\n';
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

StudentManager::StudentManager(User& user, DataRepository& data)
{
    user_ = &user;
    data_ = &data;
}

void StudentManager::login()
{
    while (true)
    {
        std::cin >> Buffer;
        String command = Buffer;
        if (command == "logout")
        {
            std::cout << "Logging out...";
            break;
        }
        if (command == "mailbox")
            mailbox();
        else if (command == "clear_mailbox")
            clear_mailbox();
        else if (command == "enroll")
        {
            std::cin >> Buffer;
            String course = Buffer;
            std::cin >> Buffer;
            String password = Buffer;
            
            enroll(course, password);
        }
        else if (command == "submit_assignment")
        {
            std::cin >> Buffer;
            String course = Buffer;
            std::cin >> Buffer;
            String assignment = Buffer;
            std::cin.getline(Buffer, BUFFER_SIZE);
            String message = Buffer;
            
            submit_assignment(course, assignment, message);
        }
        else if (command == "message")
        {
            int user_id;
            std::cin >> user_id;
            std::cin.getline(Buffer, BUFFER_SIZE);
            String temp = Buffer;
            
            message(user_id, temp);
        }
        else if (command == "grades")
            grades();
        else
            std::cout << "Invalid Command";
    }
}
