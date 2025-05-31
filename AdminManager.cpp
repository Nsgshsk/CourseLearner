#include "AdminManager.h"
#include "User.h"
#include "DataRepository.h"
#include "Student.h"
#include "Teacher.h"

namespace
{
    constexpr uint8_t BUFFER_SIZE = 255;
    char Buffer[BUFFER_SIZE + 1];

    String generatePassword(const String& str1, const String& str2)
    {
        Buffer[0] = str1[0];
        Buffer[1] = '\0';
        String password = Buffer;
        password += str2;

        return password;
    }
}

void AdminManager::add_teacher(const String& first_name, const String& last_name)
{
    add_teacher(first_name, last_name, generatePassword(first_name, last_name));
}

void AdminManager::add_teacher(const String& first_name, const String& last_name, const String& password)
{
    Teacher temp(first_name, last_name, password);
    data_->addUser(temp);
    std::cout << "Created teacher " << temp.getFullName() << " with id " << temp.getId() << '\n';
}

void AdminManager::add_student(const String& first_name, const String& last_name)
{
    add_student(first_name, last_name, generatePassword(first_name, last_name));
}

void AdminManager::add_student(const String& first_name, const String& last_name, const String& password)
{
    Student temp(first_name, last_name, password);
    data_->addUser(temp);
    std::cout << "Created student " << temp.getFullName() << " with id " << temp.getId() << '\n';
}

void AdminManager::delete_user(int user_id)
{
    try
    {
        const User& user = data_->getUser(user_id);
        data_->removeUser(user);
        std::cout << "Deleted user " << user_id << '\n';
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void AdminManager::delete_course(const String& course)
{
    try
    {
        const Course& temp = data_->getCourse(course);
        data_->removeCourse(temp);
        std::cout << "Deleted course " << course << '\n';
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void AdminManager::message_all(const String& message)
{
    const Message msg("Admin", message);
    List<User>& users = data_->getUsers();
    for (size_t i = 0; i < users.getSize(); ++i)
        try
        {
            User& user = users[i];
            user.addMessage(msg);
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    std::cout << "Sending message to all users..." << '\n';
}

void AdminManager::view_mailbox(int user_id)
{
    try
    {
        const User& user = data_->getUser(user_id);

        std::cout << "Inbox:" << '\n' << '\n';
        for (size_t i = 0; i < user.getInboxSize(); ++i)
            std::cout << '\t' << user[i];
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void AdminManager::add_teacher_input()
{
    std::cin >> Buffer;
    String first_name = Buffer;
    std::cin >> Buffer;
    String last_name = Buffer;
    std::cin.getline(Buffer, BUFFER_SIZE);
    String password = Buffer;
    
    if (password.isEmpty())
        add_teacher(first_name, last_name);
    else
    {
        const char* temp = password.c_str();
        while (*temp == ' ')
            ++temp;
        strcpy_s(Buffer, temp);
        password = Buffer;
        add_teacher(first_name, last_name, password);
    }
}

void AdminManager::add_student_input()
{
    std::cin >> Buffer;
    String first_name = Buffer;
    std::cin >> Buffer;
    String last_name = Buffer;
    std::cin.getline(Buffer, BUFFER_SIZE);
    String password = Buffer;
    
    if (password.isEmpty())
        add_student(first_name, last_name);
    else
    {
        const char* temp = password.c_str();
        while (*temp == ' ')
            ++temp;
        strcpy_s(Buffer, temp);
        password = Buffer;
        add_student(first_name, last_name, password);
    }
}

void AdminManager::delete_user_input()
{
    int user_id;
    std::cin >> user_id;

    delete_user(user_id);
}

void AdminManager::delete_course_input()
{
    std::cin >> Buffer;
    String course = Buffer;

    delete_course(course);
}

void AdminManager::message_all_input()
{
    std::cin.getline(Buffer, BUFFER_SIZE);
    String message = Buffer;

    message_all(message);
}

void AdminManager::view_mailbox_input()
{
    int user_id;
    std::cin >> user_id;

    view_mailbox(user_id);
}

AdminManager::AdminManager(User* user, DataRepository* data) : BaseManager(user, data) {}

void AdminManager::login()
{
    try
    {
        std::cout << "Admin | " << user_->getId() << '\n';
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
            else if (command == "message")
                message_input();
            else if (command == "change_password")
                change_password_input();
            else if (command == "add_teacher")
                add_teacher_input();
            else if (command == "add_student")
                add_student_input();
            else if (command == "delete_user")
                delete_user_input();
            else if (command == "delete_course")
                delete_course_input();
            else if (command == "message_all")
                message_all_input();
            else if (command == "view_mailbox")
                view_mailbox_input();
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
