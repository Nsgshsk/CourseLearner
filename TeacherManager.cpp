#include "TeacherManager.h"

#include "Course.h"
#include "String.h"
#include "User.h"
#include "DataRepository.h"

namespace
{
    constexpr uint8_t BUFFER_SIZE = 255;
    char Buffer[BUFFER_SIZE + 1];

    String generateRandomString()
    {
        std::time_t now = time(nullptr);
        ctime_s(Buffer, BUFFER_SIZE, &now);
        return Buffer;
    }
}

void TeacherManager::create_course(const String& course) const
{
    create_course(course, generateRandomString());
}

void TeacherManager::create_course(const String& course, const String& password) const
{
    data_->addCourse(Course(course, password, user_->getId()));
    std::cout << "Created course: " << course << '\n';
}

void TeacherManager::set_course_password(const String& course, const String& password) const
{
    try
    {
        Course& temp = data_->getCourse(course);
        if (!temp.isCreator(user_->getId()))
            throw std::invalid_argument("You don't have permission on this course");

        temp.changePassword(password);
        std::cout << "Changed course password successfully!\n"; 
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void TeacherManager::add_to_course(const String& course, int user_id) const
{
    try
    {
        Course& temp = data_->getCourse(course);
        if (!temp.isCreator(user_->getId()))
            throw std::invalid_argument("You don't have permission on this course");

        User& participant = data_->getUser(user_id);
        temp.enroll(participant.getId());
        Message msg(user_->getFullName(), "You have been enrolled to " + course + "!");
        participant.addMessage(msg);
        std::cout << "Enrolled " << user_id << " into " << course << "!\n";
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void TeacherManager::assign_homework(const String& course, const String& title) const
{
    try
    {
        Course& temp = data_->getCourse(course);
        if (!temp.isCreator(user_->getId()))
            throw std::invalid_argument("You don't have permissions on this course");

        temp.createAssignment(title);
        std::cout << "Created assignment successfully!\n";
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void TeacherManager::grade_homework(const String& course, const String& title, int user_id, double grade,
    const String& message) const
{
    try
    {
        Course& temp = data_->getCourse(course);
        if (!temp.isCreator(user_->getId()))
            throw std::invalid_argument("You don't have permissions on this course");

        temp.gradeSubmission(title, user_id, grade, message, user_->getId());
        std::cout << "Graded submission by " << user_id << "\n";
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void TeacherManager::message_students(const String& course, const String& message) const
{
    try
    {
        Course& temp = data_->getCourse(course);
        if (!temp.isCreator(user_->getId()))
            throw std::invalid_argument("You don't have permissions on this course");

        List<int> students = temp.getParticipantsIds();
        const Message msg(user_->getFullName(), message);
        for (size_t i = 0; i < students.getSize(); i++)
            try
            {
                User& student = data_->getUser(students[i]);
                student.addMessage(msg);
            }
            catch (...)
            {
                continue;
            }

        std::cout << "Message sent to all students!\n";
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void TeacherManager::create_course_input() const
{
    std::cin >> Buffer;
    String course = Buffer;
    std::cin.getline(Buffer, BUFFER_SIZE);
    String password = Buffer;

    if (password.isEmpty())
        create_course(course);
    else
        create_course(course, password);
}

void TeacherManager::add_to_course_input() const
{
    std::cin >> Buffer;
    String course = Buffer;
    int user_id;
    std::cin >> user_id;

    add_to_course(course, user_id);
}

void TeacherManager::assign_homework_input() const
{
    std::cin >> Buffer;
    String course = Buffer;
    std::cin >> Buffer;
    String title = Buffer;

    assign_homework(course, title);
}

void TeacherManager::grade_homework_input() const
{
    std::cin >> Buffer;
    String course = Buffer;
    std::cin >> Buffer;
    String title = Buffer;
    int user_id;
    std::cin >> user_id;
    double grade;
    std::cin >> grade;
    std::cin.getline(Buffer, BUFFER_SIZE);
    String message = Buffer;
    
    grade_homework(course, title, user_id, grade, title);
}

void TeacherManager::message_students_input() const
{
    std::cin >> Buffer;
    String course = Buffer;
    std::cin.getline(Buffer, BUFFER_SIZE);
    String message = Buffer;

    message_students(course, message);
}

void TeacherManager::set_course_password_input() const
{
    std::cin >> Buffer;
    String course = Buffer;
    std::cin >> Buffer;
    String password = Buffer;

    set_course_password(course, password);
}

TeacherManager::TeacherManager(User* user, DataRepository* data) : BaseManager(user, data) {}

void TeacherManager::login()
{
    try
    {
        std::cout << *user_ << '\n';
        while (true)
        {
            std::cout << "> ";
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
            else if (command == "message")
                message_input();
            else if (command == "change_password")
                change_password_input();
            else if (command == "create_course")
                create_course_input();
            else if (command == "add_to_course")
                add_to_course_input();
            else if (command == "assign_homework")
                assign_homework_input();
            else if (command == "grade_homework")
                grade_homework_input();
            else if (command == "message_students")
                message_students_input();
            else if (command == "set_course_password")
                set_course_password_input();
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
