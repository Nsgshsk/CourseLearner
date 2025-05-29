#pragma once
#include <cstdint>

#include "ISerializable.h"
#include "String.h"

class Submission : public ISerializable, public ISerializableDebug
{
    struct Grade : ISerializable, ISerializableDebug
    {
        uint8_t grade;
        int teacher_id;
        String message;

        Grade();
        Grade(uint8_t grade, const String& message, int teacher_id);
        
        void serialize(std::ofstream& ofs) const override;
        void deserialize(std::ifstream& ifs) override;
        void serialize_debug(std::ofstream& ofs) const override;
        void deserialize_debug(std::ifstream& ifs) override;
    };
    
    String message_;
    Grade grade_;
    int student_id_;
public:
    Submission();
    Submission(const String& message, int student_id);

    void grade(uint8_t grade, const String& message, int teacher_id);
    int getStudentId() const;
    
    void serialize(std::ofstream& ofs) const override;
    void deserialize(std::ifstream& ifs) override;
    void serialize_debug(std::ofstream& ofs) const override;
    void deserialize_debug(std::ifstream& ifs) override;
};
