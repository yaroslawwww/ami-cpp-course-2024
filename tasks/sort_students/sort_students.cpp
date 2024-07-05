#include <tuple>
#include <algorithm>
#include "sort_students.h"

bool Compare_students_by_date(const Student &x,const Student &y) {
    return std::tie(x.birth_date.year,
                    x.birth_date.month,
                    x.birth_date.day,
                    x.last_name, x.name)
           < std::tie(y.birth_date.year,
                      y.birth_date.month,
                      y.birth_date.day,
                      y.last_name, y.name);
}

bool Compare_students_by_name(const Student &x,const Student &y) {
    return std::tie(x.last_name, x.name,
                    x.birth_date.year,
                    x.birth_date.month,
                    x.birth_date.day)
           < std::tie(y.last_name, y.name,
                      y.birth_date.year,
                      y.birth_date.month,
                      y.birth_date.day);
}

void SortStudents(std::vector<Student> &students, SortKind sortKind) {
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), Compare_students_by_date);
    } else if (sortKind == SortKind::Name) {
        std::sort(students.begin(), students.end(), Compare_students_by_name);
    }
}
