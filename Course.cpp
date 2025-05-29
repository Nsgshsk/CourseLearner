#include "Course.h"
#include <fstream>

static constexpr int TEACHER_PREFIX = 2000;
static constexpr int STUDENT_PREFIX = 1000;

Course::Assignment::Assignment(const String& name)
{
    this->name = name;
}

void Course::Assignment::serialize(std::ofstream& ofs) const
{
    size_t temp = name.length();
    ofs.write((char*)&temp, sizeof(size_t));
    ofs.write(name.c_str(), temp + 1);

    temp = submissions.getSize();
    ofs.write((const char*)&temp, sizeof(size_t));
    for (size_t i = 0; i < submissions.getSize(); i++)
        submissions[i].serialize(ofs);
}

void Course::Assignment::deserialize(std::ifstream& ifs)
{
    size_t temp;
    ifs.read((char*)&temp, sizeof(size_t));
    char* str = new char[temp + 1];
    ifs.read(str, temp + 1);
    name = str;
    delete[] str;

    ifs.read((char*)&temp, sizeof(size_t));
    for (size_t i = 0; i < temp; i++)
    {
        Submission sub;
        sub.deserialize(ifs);
        submissions.add(sub);
    }
}

void Course::Assignment::serialize_debug(std::ofstream& ofs) const
{
    ofs << name.length() << '\n';
    ofs << name << '\n';
    
    ofs << submissions.getSize() << '\n';
    for (size_t i = 0; i < submissions.getSize(); i++)
        submissions[i].serialize_debug(ofs);
}

void Course::Assignment::deserialize_debug(std::ifstream& ifs)
{
    ifs >> name;

    size_t temp;
    ifs >> temp;
    for (size_t i = 0; i < temp; i++)
        submissions[i].deserialize_debug(ifs);
}

Course::Course() = default;

Course::Course(const String& name, const String& password)
{
    name_ = name;
    password_ = password;
}

void Course::enroll(int participant_id)
{
    if (participant_id % TEACHER_PREFIX < STUDENT_PREFIX)
    {
        participants_ids_.add(participant_id);
        return;
    }

    throw std::invalid_argument("Participant not allowed");
}

void Course::enroll(int participant_id, const String& password)
{
    if (password_ == password)
    {
        participants_ids_.add(participant_id);
        return;
    }

    throw std::invalid_argument("Invalid password");
}

void Course::createAssignment(const String& name)
{
    assignments_.add(Assignment(name));
}

void Course::submitAssignment(const String& name, const String& message, int student_id)
{
    for (size_t i = 0; i < assignments_.getSize(); i++)
        if (assignments_[i].name == name)
        {
            assignments_[i].submissions.add(Submission(message, student_id));
            return;
        }

    throw std::invalid_argument("Assignment doesn't exist");
}

void Course::gradeSubmission(const String& name, int student_id, uint8_t grade, const String& message)
{
    for (size_t i = 0; i < assignments_.getSize(); i++)
        if (assignments_[i].name == name)
        {
            List<Submission>& temp = assignments_[i].submissions;
            for (size_t j = 0; j < temp.getSize(); j++)
                if (temp[j].getStudentId() == student_id)
                {
                    temp[j].grade(grade, message, TODO);
                    return;
                }
            
            throw std::invalid_argument("Submission doesn't exist");
        }
    
    throw std::invalid_argument("Assignment doesn't exist");
}

void Course::serialize(std::ofstream& ofs) const
{
    size_t temp = name_.length();
    ofs.write((char*)&temp, sizeof(size_t));
    ofs.write(name_.c_str(), temp + 1);

    temp = password_.length();
    ofs.write((char*)&temp, sizeof(size_t));
    ofs.write(password_.c_str(), temp + 1);

    temp = assignments_.getSize();
    ofs.write((char*)&temp, sizeof(size_t));
    for (size_t i = 0; i < assignments_.getSize(); i++)
        assignments_[i].serialize(ofs);

    temp = participants_ids_.getSize();
    ofs.write((char*)&temp, sizeof(size_t));
    for (size_t i = 0; i < participants_ids_.getSize(); i++)
        ofs.write((const char*)&participants_ids_[i], sizeof(int));
}

void Course::deserialize(std::ifstream& ifs)
{
    size_t temp;
    ifs.read((char*)&temp, sizeof(size_t));
    char* str = new char[temp + 1];
    ifs.read(str, temp + 1);
    name_ = str;
    delete[] str;

    ifs.read((char*)&temp, sizeof(size_t));
    str = new char[temp + 1];
    ifs.read(str, temp + 1);
    password_ = str;
    delete[] str;

    ifs.read((char*)&temp, sizeof(size_t));
    for (size_t i = 0; i < temp; i++)
        assignments_[i].deserialize(ifs);

    ifs.read((char*)&temp, sizeof(size_t));
    for (size_t i = 0; i < temp; i++)
    {
        int id;
        ifs.read((char*)&id, sizeof(int));
        participants_ids_.add(id);
    }
}

void Course::serialize_debug(std::ofstream& ofs) const
{
    ofs << name_.length() << '\n';
    ofs << name_ << '\n';

    ofs << password_.length() << '\n';
    ofs << password_ << '\n';

    ofs << assignments_.getSize() << '\n';
    for (size_t i = 0; i < assignments_.getSize(); i++)
        assignments_[i].serialize_debug(ofs);

    ofs << participants_ids_.getSize() << '\n';
    for (size_t i = 0; i < participants_ids_.getSize(); i++)
        ofs << participants_ids_[i] << '\n';
}

void Course::deserialize_debug(std::ifstream& ifs)
{
    ifs >> name_;
    ifs >> password_;

    size_t temp;
    ifs >> temp;
    for (size_t i = 0; i < temp; i++)
        assignments_[i].deserialize_debug(ifs);

    ifs >> temp;
    for (size_t i = 0; i < temp; i++)
    {
        int id;
        ifs >> id;
        participants_ids_.add(id);
    }
}
