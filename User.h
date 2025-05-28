#pragma once
#include "ISerializable.h"
#include "List.hpp"
#include "Message.h"
#include "String.h"

class User : public ISerializable, public ISerializableDebug
{
    int id_;
    String first_name_;
    String last_name_;
    String password_;
    List<Message> inbox_;

protected:
    virtual void generate_id() = 0;
    void setId(int id);

public:
    User();
    User(const String& first_name, const String& last_name, const String& password);
    
    int getId() const;
    
    size_t getInboxSize() const;
    const Message& operator[](size_t index) const;

    void addMessage(const Message& message);
    void clearMessages();

    void serialize(std::ofstream& ofs) const override;
    void deserialize(std::ifstream& ifs) override;

    void serialize_debug(std::ofstream& ofs) const override;
    void deserialize_debug(std::ifstream& ifs) override;

    friend std::ostream& operator<<(std::ostream& os, const User& user);
};
