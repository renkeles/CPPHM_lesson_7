#include <iostream>
#include <cstdlib>
#include <tuple>
#include <fstream>
#include <string>
#include <vector>
#include "fullname.pb.h"

class IRepository {
    virtual void Open() = 0; // бинарная десериализация в файл
    virtual void Save() = 0; // бинарная сериализация в файл
};

class IMethods {
    virtual double GetAverageScore(const FullName& name) = 0;
    virtual std::string GetAllInfo(const FullName& name) = 0;
    virtual std::string GetAllInfo() = 0;
};


class StudentsGroup : public IRepository, public IMethods {
private:
    std::vector<Student> _students;
public:
    [[nodiscard]] std::vector<Student> GetStudents() const { return _students; }
    void Open(const std::string& filename) {
        std::ifstream in(filename, std::ios_base::binary);
        size_t size = 0;

        while (size--) {
            Student student;
            student.ParseFromIstream(&in);
            _students.push_back(std::move(student));
        }
        in.close();
    }

    void Save() override {
        std::ofstream out("_students.bin", std::ios_base::binary);

        for (auto& student : _students) {
            student.SerializePartialToOstream(&out);
        }
        out.close();
    }

    void Push(Student&& student) {
        _students.push_back(student);
    }

    double GetAverageScore(const FullName& rhs) override {
        auto student = [&](const Student& lhs) {
            return std::tie(lhs.fullname().name(), lhs.fullname().surname(), lhs.fullname().patronymic()) ==
                   std::tie(rhs.name(), rhs.surname(), rhs.patronymic());
        };
        auto iter { std::find_if(_students.begin(), _students.end(), student) };
        return iter->averagescore();
    }
    std::string GetAllInfo(const FullName& rhs) override {
        std::string information;
        auto student = [&](const Student& lhs) {
            return std::tie(lhs.fullname().name(), lhs.fullname().surname(), lhs.fullname().patronymic()) ==
                   std::tie(rhs.name(), rhs.surname(), rhs.patronymic());
        };
        auto iter = std::find_if(_students.begin(), _students.end(), student);
        information.append(iter->fullname().name());
        information.push_back(' ');
        information.append((iter->fullname().has_patronymic() ? iter->fullname().patronymic() : ""));
        information.push_back(' ');
        information.append(iter->fullname().surname());
        information.push_back('\t');
        for (const auto& g : iter->rating()) {
            information.append(std::to_string(g));
            information.push_back(' ');
        }
        information.push_back('\t');
        information.append(std::to_string(iter->averagescore()));
        return information;
    }

    std::string GetAllInfo() override {
        std::string information;
        auto iter { _students.begin() };
        while (iter != _students.end()) {
            information.append(GetAllInfo(iter->fullname()));
            information.push_back('\n');
            iter++;
        }
        return information;
    }
};


int main() {

    return 0;
}
