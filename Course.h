#pragma once

#include "ISerializable.h"
#include "List.hpp"
#include "SerializableList.hpp"
#include "String.h"
#include "Submission.h"

class Course final : public ISerializable, public ISerializableDebug
{
    struct Assignment : ISerializable, ISerializableDebug
    {
        String name;
        List<Submission> submissions;

        Assignment(const String& name);

        const Submission* getUserSubmission(int user_id) const;
        
        void serialize(std::ofstream& ofs) const override;
        void deserialize(std::ifstream& ifs) override;
        void serialize_debug(std::ofstream& ofs) const override;
        void deserialize_debug(std::ifstream& ifs) override;
    };

    int teacher_id_;
    String name_;
    String password_;
    SerializableList<Assignment> assignments_;
    List<int> participants_ids_;
public:
    Course();
    Course(const String& name, const String& password, int teacher_id);

    bool isCreator(int user_id) const;
    const String& getName() const;
    bool validatePassword(const String& password) const;
    void changePassword(const String& new_password);
    bool isUserEnrolled(int user_id) const;

    List<int> getParticipantsIds() const;

    void enroll(int participant_id);
    void enroll(int participant_id, const String& password);
    
    void createAssignment(const String& name);
    void submitAssignment(const String& name, const String& message, int student_id);
    void gradeSubmission(const String& name, int student_id, double grade, const String& message, int teacher_id);

    List<Submission> getUserAssignments(int user_id) const;

    bool operator==(const Course& rhs) const;
    
    void serialize(std::ofstream& ofs) const override;
    void deserialize(std::ifstream& ifs) override;
    void serialize_debug(std::ofstream& ofs) const override;
    void deserialize_debug(std::ifstream& ifs) override;
};
bool operator!=(const Course& lhs, const Course& rhs);
