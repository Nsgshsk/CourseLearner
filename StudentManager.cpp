#include "StudentManager.h"

#include "DataRepository.h"
#include "User.h"
#include "Course.h"

namespace
{
    constexpr uint8_t BUFFER_SIZE = 255;
    char Buffer[BUFFER_SIZE + 1];
}

void StudentManager::enroll(const String& course, const String& password) const
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

void StudentManager::submit_assignment(const String& course, const String& assignment, const String& message) const
{
    try
    {
        Course& temp = data_->getCourse(course);
        if (!temp.isUserEnrolled(user_->getId()))
            throw std::invalid_argument("User has not enrolled in the course!");

        temp.submitAssignment(assignment, message, user_->getId());
        std::cout << "Successfully submitted assignment into " << course << "!\n";
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void StudentManager::grades() const
{
    try
    {
        const List<String>& courses = user_->getCourses();
        std::cout << "Grades:\n\n";
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

StudentManager::StudentManager(User* user, DataRepository* data) : BaseManager(user, data) {}

void StudentManager::enroll_input() const
{
    std::cin >> Buffer;
    String course = Buffer;
    std::cin >> Buffer;
    String password = Buffer;
            
    enroll(course, password);
}

void StudentManager::submit_assignment_input() const
{
    std::cin >> Buffer;
    String course = Buffer;
    std::cin >> Buffer;
    String assignment = Buffer;
    std::cin.getline(Buffer, BUFFER_SIZE);
    String message = Buffer;
            
    submit_assignment(course, assignment, message);
}

void StudentManager::login()
{
    try
    {
        std::cout << "Login successful!\n";
        std::cout << *user_ << '\n';
        while (true)
        {
            std::cout << ">";
            std::cin >> Buffer;
            String command = Buffer;
            if (command == "logout")
            {
                std::cout << "Logging out...\n";
                break;
            }
            if (command == "mailbox")
                mailbox();
            else if (command == "clear_mailbox")
                clear_mailbox();
            else if (command == "enroll")
                enroll_input();
            else if (command == "submit_assignment")
                submit_assignment_input();
            else if (command == "message")
                message_input();
            else if (command == "change_password")
                change_password_input();
            else if (command == "grades")
                grades();
            else
                std::cout << "Invalid Command\n";
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
        std::cout << "!!! Fatal error !!!\n";
    }
}
