#include "Submission.h"
#include <fstream>

Submission::Grade::Grade() = default;

Submission::Grade::Grade(double grade, const String& message, int teacher_id)
{
    if (grade < 2 || grade > 6)
        throw std::invalid_argument("grade must be between 2 and 6");
    this->grade = grade;
    this->message = message;
    this->teacher_id = teacher_id;
}

void Submission::Grade::serialize(std::ofstream& ofs) const
{
    ofs.write((const char*)&grade, sizeof(double));
    ofs.write((const char*)&teacher_id, sizeof(int));

    size_t temp = message.length();
    ofs.write(message.c_str(), temp + 1);
}

void Submission::Grade::deserialize(std::ifstream& ifs)
{
    ifs.read((char*)&grade, sizeof(double));
    ifs.read((char*)&teacher_id, sizeof(int));

    size_t temp;
    ifs.read((char*)&temp, sizeof(size_t));
    char* str = new char[temp + 1];
    ifs.read(str, temp + 1);
    message = str;
    delete[] str;
}

void Submission::Grade::serialize_debug(std::ofstream& ofs) const
{
    ofs << grade << '\n';
    ofs << teacher_id << '\n';

    ofs << message.length() << '\n';
    ofs << message << '\n';
}

void Submission::Grade::deserialize_debug(std::ifstream& ifs)
{
    ifs >> grade >> teacher_id >> message;
}

Submission::Submission() = default;

Submission::Submission(const String& message, int student_id, const String& assignment_title)
{
    message_ = message;
    student_id_ = student_id;
    assignment_title_ = assignment_title;
}

void Submission::grade(double grade, const String& message, int teacher_id)
{
    grade_ = Grade(grade, message, teacher_id);
}

int Submission::getStudentId() const
{
    return student_id_;
}

const String& Submission::getStudentMessage() const
{
    return message_;
}

void Submission::serialize(std::ofstream& ofs) const
{
    ofs.write((const char*)&student_id_, sizeof(int));

    size_t temp = message_.length();
    ofs.write((const char*)&temp, sizeof(size_t));
    ofs.write(message_.c_str(), temp + 1);

    temp = assignment_title_.length();
    ofs.write((const char*)&temp, sizeof(size_t));
    ofs.write(assignment_title_.c_str(), temp + 1);

    grade_.serialize(ofs);
}

void Submission::deserialize(std::ifstream& ifs)
{
    ifs.read((char*)&student_id_, sizeof(int));

    size_t temp;
    ifs.read((char*)&temp, sizeof(size_t));
    char* str = new char[temp + 1];
    ifs.read(str, temp + 1);
    message_ = str;
    delete[] str;
    
    ifs.read((char*)&temp, sizeof(size_t));
    str = new char[temp + 1];
    ifs.read(str, temp + 1);
    assignment_title_ = str;
    delete[] str;

    grade_.deserialize(ifs);
}

void Submission::serialize_debug(std::ofstream& ofs) const
{
    ofs << student_id_ << '\n';
    
    ofs << message_.length() << '\n';
    ofs << message_ << '\n';

    ofs << assignment_title_.length() << '\n';
    ofs << assignment_title_ << '\n';

    grade_.serialize_debug(ofs);
}

void Submission::deserialize_debug(std::ifstream& ifs)
{
    ifs >> student_id_ >> message_ >> assignment_title_;

    grade_.deserialize_debug(ifs);
}

std::ostream& operator<<(std::ostream& os, const Submission& submission)
{
    os << submission.assignment_title_ << " | ";
    os << submission.grade_.grade << " | ";
    os << submission.grade_.message << '\n';
    
    return os;
}
