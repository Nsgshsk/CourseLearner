#include "Submission.h"
#include <fstream>

Submission::Grade::Grade() = default;

Submission::Grade::Grade(uint8_t grade, const String& message, int teacher_id)
{
    this->grade = grade;
    this->message = message;
    this->teacher_id = teacher_id;
}

void Submission::Grade::serialize(std::ofstream& ofs) const
{
    ofs.write((const char*)&grade, sizeof(uint8_t));
    ofs.write((const char*)&teacher_id, sizeof(int));

    size_t temp = message.length();
    ofs.write(message.c_str(), temp + 1);
}

void Submission::Grade::deserialize(std::ifstream& ifs)
{
    ifs.read((char*)&grade, sizeof(uint8_t));
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

Submission::Submission(const String& message, int student_id)
{
    message_ = message;
    student_id_ = student_id;
}

void Submission::grade(uint8_t grade, const String& message, int teacher_id)
{
    grade_ = Grade(grade, message, teacher_id);
}

int Submission::getStudentId() const
{
    return student_id_;
}

void Submission::serialize(std::ofstream& ofs) const
{
    ofs.write((const char*)&student_id_, sizeof(int));

    size_t temp = message_.length();
    ofs.write((const char*)&temp, sizeof(size_t));
    ofs.write(message_.c_str(), temp + 1);

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

    grade_.deserialize(ifs);
}

void Submission::serialize_debug(std::ofstream& ofs) const
{
    ofs << student_id_ << '\n';
    
    ofs << message_.length() << '\n';
    ofs << message_ << '\n';

    grade_.serialize_debug(ofs);
}

void Submission::deserialize_debug(std::ifstream& ifs)
{
    ifs >> student_id_ >> message_;

    grade_.deserialize_debug(ifs);
}
