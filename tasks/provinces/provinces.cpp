#include "provinces.h"

#include <set>

int64_t CountPassports(const std::vector<int>& provinces) {
    std::multiset<int64_t> provinces_copy;
    for (int i : provinces) {
        provinces_copy.insert(i);
    }
    int64_t new_passports = 0;
    while (provinces_copy.size() != 1) {
        int64_t new_province = *provinces_copy.begin();
        provinces_copy.erase(provinces_copy.begin());
        new_province += *provinces_copy.begin();
        provinces_copy.erase(provinces_copy.begin());
        new_passports += new_province;
        provinces_copy.insert(new_province);
    }
    return new_passports;
}
