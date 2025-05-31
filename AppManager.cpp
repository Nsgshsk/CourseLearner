#include "AppManager.h"

#include "Admin.h"
#include "String.h"
#include "AdminManager.h"
#include "TeacherManager.h"
#include "StudentManager.h"
#include "User.h"

namespace
{
    constexpr uint8_t BUFFER_SIZE = 255;
    char Buffer[BUFFER_SIZE + 1];
}

void AppManager::login()
{
    try
    {
        int id;
        std::cin >> id;
        std::cin >> Buffer;
        String password = Buffer;

        User& user = data_.getUser(id);
        if (!user.validatePassword(password))
            throw std::invalid_argument("Invalid password");

        int type = user.getType();
        if (type == 1)
        {
            AdminManager am(&user, &data_);
            am.login();
        }
        else if (type == 2)
        {
            TeacherManager tm(&user, &data_);
            tm.login();
        }
        else if (type == 3)
        {
            StudentManager sm(&user, &data_);
            sm.login();
        }
        else
            throw std::invalid_argument("Invalid User Type");
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

AppManager::AppManager()
{
    try
    {
        data_.loadDataDebug();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
        std::cout << "Creating new database...";
        data_.addUser(Admin("admin", "admin", "0000"));
    }
}

AppManager::~AppManager()
{
    try
    {
        data_.saveDataDebug();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
        std::cout << "!!! Data not saved !!!";
    }
}

void AppManager::run()
{
    while (true)
    {
        std::cin >> Buffer;
        String command = Buffer;
        if (command == "exit")
        {
            std::cout << "Shutting down...";
            break;
        }
        if (command == "login")
            login();
        else
            std::cout << "Invalid Command";
    }
}
