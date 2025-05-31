#pragma once
#include <cstdint>

#include "ISerializable.h"
#include "String.h"

class Submission : public ISerializable, public ISerializableDebug
{
    struct Grade : ISerializable, ISerializableDebug
    {
        double grade;
        int teacher_id;
        String message;

        Grade();
        Grade(double grade, const String& message, int teacher_id);
        
        void serialize(std::ofstream& ofs) const override;
        void deserialize(std::ifstream& ifs) override;
        void serialize_debug(std::ofstream& ofs) const override;
        void deserialize_debug(std::ifstream& ifs) override;
    };

    String assignment_title_;
    String message_;
    Grade grade_;
    int student_id_;
public:
    Submission();
    Submission(const String& message, int student_id, const String& assignment_title);

    void grade(double grade, const String& message, int teacher_id);
    int getStudentId() const;
    const String& getStudentMessage() const;
    
    void serialize(std::ofstream& ofs) const override;
    void deserialize(std::ifstream& ifs) override;
    void serialize_debug(std::ofstream& ofs) const override;
    void deserialize_debug(std::ifstream& ifs) override;

    friend std::ostream& operator<<(std::ostream& os, const Submission& submission);
};
