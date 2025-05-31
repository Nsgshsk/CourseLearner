#pragma once
#include "ISerializable.h"
#include "List.hpp"
#include "Message.h"
#include "String.h"

enum UserType
{
    ADMIN = 1,
    TEACHER,
    STUDENT
};

class User : public ISerializable, public ISerializableDebug
{
    int id_;
    UserType type_;
    String first_name_;
    String last_name_;
    String password_;
    List<Message> inbox_;
    List<String> courses;

protected:
    virtual void generate_id();
    void setId(int id);

public:
    User();
    User(const String& first_name, const String& last_name, const String& password, UserType type);
    
    int getId() const;
    int getType() const;
    String getFirstName() const;
    String getLastName() const;
    String getFullName() const;
    
    bool validatePassword(const String& password) const;
    void changePassword(const String& old_password, const String& new_password);
    
    size_t getInboxSize() const;
    const Message& operator[](size_t index) const;

    void addMessage(const Message& message);
    void clearMessages();

    const List<String>& getCourses() const;
    void addCourse(const String& course);
    void clearCourses();

    void serialize(std::ofstream& ofs) const override;
    void deserialize(std::ifstream& ifs) override;

    void serialize_debug(std::ofstream& ofs) const override;
    void deserialize_debug(std::ifstream& ifs) override;

    bool operator==(const User& rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};

bool operator!=(const User& lhs, const User& rhs);
