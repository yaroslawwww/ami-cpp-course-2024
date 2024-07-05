#include <deque>
#include <string_view>
#include "tests_checking.h"

std::vector<std::string> StudentsOrder(const std::vector<StudentAction> &student_actions,
                                       const std::vector<size_t> &queries) {
    std::deque<std::string_view> tests;

    for (const StudentAction &action : student_actions) {
        if (action.side == Side::Top) {
            tests.push_front(action.name);
        } else {
            tests.push_back(action.name);
        }
    }
    std::vector<std::string> students;
    for (size_t number : queries) {
        students.push_back(std::string{tests[number - 1]});
    }
    return students;
}
