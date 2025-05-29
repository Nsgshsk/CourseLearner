#include "User.h"
#include <fstream>

static constexpr int TEACHER_PREFIX = 2000;
static constexpr int STUDENT_PREFIX = 1000;

void User::setId(int id)
{
    id_ = id;
}

User::User() = default;

User::User(const String& first_name, const String& last_name, const String& password) : id_(0)
{
    first_name_ = first_name;
    last_name_ = last_name;
    password_ = password;
}

int User::getId() const
{
    return id_;
}

int User::getType() const
{
    if (getId() < STUDENT_PREFIX)
        return 1;
    if (getId() % TEACHER_PREFIX < STUDENT_PREFIX)
        return 2;
    if (getId() % STUDENT_PREFIX < STUDENT_PREFIX)
        return 3;

    return -1;
}

bool User::validatePassword(const String& password)
{
    return password_ == password;
}

size_t User::getInboxSize() const
{
    return inbox_.getSize();
}

const Message& User::operator[](size_t index) const
{
    return inbox_[index];
}

void User::addMessage(const Message& message)
{
    inbox_.add(message);
}

void User::clearMessages()
{
    inbox_.clear();
}

void User::serialize(std::ofstream& ofs) const
{
    ofs.write((const char*)&id_, sizeof(int));
    
    size_t temp = first_name_.length();
    ofs.write((const char*)&temp, sizeof(size_t));
    ofs.write(first_name_.c_str(), temp + 1);

    temp = last_name_.length();
    ofs.write((const char*)&temp, sizeof(size_t));
    ofs.write(last_name_.c_str(), temp + 1);

    temp = password_.length();
    ofs.write((const char*)&temp, sizeof(size_t));
    ofs.write(password_.c_str(), temp + 1);
    
    for (size_t i = 0; i < inbox_.getSize(); i++)
        inbox_[i].serialize(ofs);
}

void User::deserialize(std::ifstream& ifs)
{
    ifs.read((char*)&id_, sizeof(int));
    
    size_t temp;
    ifs.read((char*)&temp, sizeof(size_t));
    char* str = new char[temp + 1];
    ifs.read(str, temp + 1);
    first_name_ = str;
    delete[] str;

    ifs.read((char*)&temp, sizeof(size_t));
    str = new char[temp + 1];
    ifs.read(str, temp + 1);
    last_name_ = str;
    delete[] str;

    ifs.read((char*)&temp, sizeof(size_t));
    str = new char[temp + 1];
    ifs.read(str, temp + 1);
    password_ = str;
    delete[] str;

    for (size_t i = 0; i < inbox_.getSize(); i++)
    {
        Message message;
        ifs.read((char*)&message, sizeof(Message));
        addMessage(message);
    }
}

void User::serialize_debug(std::ofstream& ofs) const
{
    ofs << id_ << '\n';
    
    ofs << first_name_.length() << '\n';
    ofs << first_name_ << '\n';

    ofs << last_name_.length() << '\n';
    ofs << last_name_ << '\n';

    ofs << password_.length() << '\n';
    ofs << password_ << '\n';

    for (size_t i = 0; i < inbox_.getSize(); i++)
        inbox_[i].serialize_debug(ofs);
}

void User::deserialize_debug(std::ifstream& ifs)
{
    ifs >> first_name_;
    ifs >> last_name_;
    ifs >> password_;

    for (size_t i = 0; i < inbox_.getSize(); i++)
    {
        Message message;
        message.deserialize_debug(ifs);
        inbox_.add(message);
    }
}

bool User::operator==(const User& rhs) const
{
    return id_ == rhs.id_;
}

bool operator!=(const User& lhs, const User& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const User& user)
{
    os << user.first_name_ << " | ";
    os << user.last_name_ << " | ";
    switch (user.getType())
    {
        case 1:
            os << "Admin";
            break;
        case 2:
            os << "Teacher";
            break;
        case 3:
            os << "Student";
            break;

        default:
            throw std::invalid_argument("Invalid User Type");
    }

    os << " | ";
    os << user.getId() << '\n';
    return os;
}
