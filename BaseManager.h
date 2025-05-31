#pragma once

class User;
class DataRepository;
class String;

class BaseManager
{
protected:
    User* user_;
    DataRepository* data_;
    
    void change_password(const String& old_password, const String& new_password) const;
    void mailbox() const;
    void clear_mailbox() const;
    void message(int user_id, const String& message) const;
    void message_input() const;
    void change_password_input() const;

public:
    BaseManager(User* user, DataRepository* data);
    virtual ~BaseManager();
    virtual void login();
};
