#include <iostream>
#include "fullname.pb.h"

int main() {

    FullName fullName;
    fullName.set_surname("Pupkin");
    fullName.set_name("Vasya");
    fullName.set_patronymic("Petrov");

    std::cout << fullName.surname() << " " << fullName.name() << " " << fullName.patronymic();

    Student student;


    student.add_rating(3);
    student.add_rating(3);
    std::cout << student.rating().size();


    std::vector<Student> students;


    return 0;
}
