﻿#include "Message.h"
#include <iostream>
#include <fstream>

Message::Message() = default;

Message::Message(String sender, String message) : sender_(std::move(sender)), message_(std::move(message))
{
    // Setting current DateTime of message
    std::time_t now = time(nullptr);
    ctime_s(dateTime_, DATE_TIME_MAX_SIZE, &now);
}

// Serializes message into a binary file
void Message::serialize(std::ofstream& ofs) const
{
    size_t temp = sender_.length();
    ofs.write((const char*)&temp, sizeof(size_t));
    ofs.write(sender_.c_str(), temp + 1);

    ofs.write(dateTime_, DATE_TIME_MAX_SIZE);

    temp = message_.length();
    ofs.write((const char*)&temp, sizeof(size_t));
    ofs.write(message_.c_str(), temp + 1);
}

// Deserializes message from a binary file
void Message::deserialize(std::ifstream& ifs)
{
    size_t temp; // Temporary variable for lengths
    char* str; // Temporary variable for strings

    // Sender string deserialization from binary
    ifs.read((char*)&temp, sizeof(size_t)); // Sender string length
    str = new char[temp + 1];
    ifs.read(str, temp + 1);
    sender_ = str;
    delete[] str;

    // Datetime string deserialization from binary
    ifs.read(dateTime_, DATE_TIME_MAX_SIZE);

    // Message string deserialization from text
    ifs.read((char*)&temp, sizeof(size_t)); // Message string length
    str = new char[temp + 1];
    ifs.read(str, temp + 1);
    message_ = str;
    delete[] str;
}

// Serializes message into a text file
void Message::serialize_debug(std::ofstream& ofs) const
{
    // Serializes sender string into text
    ofs << sender_.length() << '\n'; // Sender string length
    ofs << sender_ << '\n';

    // Serializes datetime string into text
    ofs << strlen(dateTime_) << '\n'; // Datetime string length
    ofs << dateTime_;

    // Serializes message into text
    ofs << message_.length() << '\n'; // Message string length
    ofs << message_ << '\n';
}

// Deserializes message from text file
void Message::deserialize_debug(std::ifstream& ifs)
{
    ifs >> sender_;

    size_t temp; // Temporary variable for lengths

    // Datetime string deserialization from text
    ifs >> temp; // Datetime string length
    ifs.ignore(); // Ignores the newline character
    ifs.getline(dateTime_, temp + 1);
    dateTime_[temp - 1] = '\n'; // Puts a newline character at the end of datetime string

    // Message string deserialization from text
    ifs >> temp; // Message string length
    char* str = new char[temp + 1];
    ifs.ignore(); // Ignores the newline character
    ifs.getline(str, temp + 1);
    message_ = str;
    delete[] str;
}

std::ostream& operator<<(std::ostream& os, const Message& message)
{
    os << "By " << message.sender_ << '\n';
    os << "At " << message.dateTime_ << '\n';
    os << message.message_ << '\n';
    return os;
}
