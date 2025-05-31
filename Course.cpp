#include "Course.h"
#include <fstream>

static constexpr int TEACHER_PREFIX = 2000;
static constexpr int STUDENT_PREFIX = 1000;

Course::Assignment::Assignment() = default;

Course::Assignment::Assignment(const String& name)
{
    this->name = name;
}

const Submission* Course::Assignment::getUserSubmission(int user_id) const
{
    for (size_t i = 0; i < submissions.getSize(); i++)
        if (submissions[i].getStudentId() == user_id)
            return &submissions[i];

    return nullptr;
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

Course::Course(const String& name, const String& password, int teacher_id)
{
    name_ = name;
    password_ = password;
    teacher_id_ = teacher_id;
}

bool Course::isCreator(int user_id) const
{
    return teacher_id_ == user_id;
}

const String& Course::getName() const
{
    return name_;
}

bool Course::validatePassword(const String& password) const
{
    return password_ == password;
}

void Course::changePassword(const String& new_password)
{
    password_ = new_password;
}

bool Course::isUserEnrolled(int user_id) const
{
    for (size_t i = 0; i < participants_ids_.getSize(); i++)
        if (participants_ids_[i] == user_id)
            return true;
    
    return false;
}

List<int> Course::getParticipantsIds() const
{
    return participants_ids_;
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
            assignments_[i].submissions.add(Submission(message, student_id, name));
            return;
        }

    throw std::invalid_argument("Assignment doesn't exist");
}

void Course::gradeSubmission(const String& name, int student_id, double grade, const String& message, int teacher_id)
{
    for (size_t i = 0; i < assignments_.getSize(); i++)
        if (assignments_[i].name == name)
        {
            List<Submission>& temp = assignments_[i].submissions;
            for (size_t j = 0; j < temp.getSize(); j++)
                if (temp[j].getStudentId() == student_id)
                {
                    temp[j].grade(grade, message, teacher_id);
                    return;
                }
            
            throw std::invalid_argument("Submission doesn't exist");
        }
    
    throw std::invalid_argument("Assignment doesn't exist");
}

List<Submission> Course::getUserAssignments(int user_id) const
{
    List<Submission> temp;
    for (size_t i = 0; i < assignments_.getSize(); i++)
    {
        const Submission* submission = assignments_[i].getUserSubmission(user_id);
        if (submission != nullptr)
            temp.add(*submission);
    }
    return temp;
}

bool Course::operator==(const Course& rhs) const
{
    return name_ == rhs.name_;
}

void Course::serialize(std::ofstream& ofs) const
{
    ofs.write((const char*)&teacher_id_, sizeof(int));
    
    size_t temp = name_.length();
    ofs.write((char*)&temp, sizeof(size_t));
    ofs.write(name_.c_str(), temp + 1);

    temp = password_.length();
    ofs.write((char*)&temp, sizeof(size_t));
    ofs.write(password_.c_str(), temp + 1);

    assignments_.serialize(ofs);

    temp = participants_ids_.getSize();
    ofs.write((char*)&temp, sizeof(size_t));
    for (size_t i = 0; i < participants_ids_.getSize(); i++)
        ofs.write((const char*)&participants_ids_[i], sizeof(int));
}

void Course::deserialize(std::ifstream& ifs)
{
    ifs.read((char*)&teacher_id_, sizeof(int));
    
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

    assignments_.deserialize(ifs);

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
    ofs << teacher_id_ << '\n';
    
    ofs << name_.length() << '\n';
    ofs << name_ << '\n';

    ofs << password_.length() << '\n';
    ofs << password_ << '\n';

    assignments_.serialize_debug(ofs);

    ofs << participants_ids_.getSize() << '\n';
    for (size_t i = 0; i < participants_ids_.getSize(); i++)
        ofs << participants_ids_[i] << '\n';
}

void Course::deserialize_debug(std::ifstream& ifs)
{
    ifs >> teacher_id_;
    
    ifs >> name_;
    ifs >> password_;
    
    assignments_.deserialize_debug(ifs);

    size_t temp;
    ifs >> temp;
    for (size_t i = 0; i < temp; i++)
    {
        int id;
        ifs >> id;
        participants_ids_.add(id);
    }
}

bool operator!=(const Course& lhs, const Course& rhs)
{
    return !(lhs == rhs);
}
