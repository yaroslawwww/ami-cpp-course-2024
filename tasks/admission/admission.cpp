#include <tuple>
#include <algorithm>
#include "admission.h"

bool CompareApplicantsReverse(const Applicant *&x, const Applicant *&y) {
    return std::tie(x->points, x->student.birth_date.year, x->student.birth_date.month, x->student.birth_date.day,
                    x->student.name) > std::tie(y->points, y->student.birth_date.year, y->student.birth_date.month,
                                                y->student.birth_date.day, y->student.name);
}

AdmissionTable FillUniversities(const std::vector<University> &universities, const std::vector<Applicant> &applicants) {
    AdmissionTable final_table;
    std::vector<const Applicant *> applicants_pointers;
    for (const Applicant &applicant : applicants) {
        applicants_pointers.push_back(&applicant);
    }
    std::sort(applicants_pointers.begin(), applicants_pointers.end(), CompareApplicantsReverse);
    std::vector<University> universities_copy = universities;
    for (const Applicant *applicant : applicants_pointers) {
        for (const std::basic_string<char> &desired_university : applicant->wish_list) {
            bool entered = false;
            for (University &university : universities_copy) {
                if (desired_university == university.name && university.max_students > 0) {
                    university.max_students--;
                    final_table[desired_university].push_back(&(applicant->student));
                    entered = true;
                    break;
                }
            }
            if (entered) {
                break;
            }
        }
    }
    return final_table;
}
