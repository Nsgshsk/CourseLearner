#include "BaseManager.h"

#include <cstdint>
#include "String.h"
#include "User.h"
#include "DataRepository.h"

namespace
{
    constexpr uint8_t BUFFER_SIZE = 255;
    char Buffer[BUFFER_SIZE + 1];
}

void BaseManager::change_password(const String& old_password, const String& new_password) const
{
    try
    {
        user_->changePassword(old_password, new_password);
        std::cout << "Password changed successfully!" << '\n';
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void BaseManager::mailbox() const
{
    size_t temp = user_->getInboxSize();
    if (temp == 0)
        std::cout << "We have no messages to show!\n";
    else
        for (size_t i = 0; i < temp; i++)
            std::cout << (*user_)[i];
}

void BaseManager::clear_mailbox() const
{
    user_->clearMessages();
    std::cout << "Inbox cleared!\n";
}

void BaseManager::message(int user_id, const String& message) const
{
    try
    {
        User& temp = data_->getUser(user_id);
        temp.addMessage(Message(user_->getFullName(), message));
        std::cout << "Message sent successfully!\n";
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
}

void BaseManager::message_input() const
{
    int user_id;
    std::cin >> user_id;
    std::cin.getline(Buffer, BUFFER_SIZE);
    String temp = Buffer;
            
    message(user_id, temp);
}

void BaseManager::change_password_input() const
{
    std::cin >> Buffer;
    String old_password = Buffer;
    std::cin >> Buffer;
    String new_password = Buffer;
                
    change_password(old_password, new_password);
}

BaseManager::BaseManager(User* user, DataRepository* data)
{
    user_ = user;
    data_ = data;
}

BaseManager::~BaseManager() = default;

void BaseManager::login()
{
    throw std::exception("Not implemented");
}
