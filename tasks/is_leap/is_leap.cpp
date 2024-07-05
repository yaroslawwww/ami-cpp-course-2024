#include "is_leap.h"

bool IsLeap(int year) {
    const int hundred = 100;
    const int four_hundred = 400;
    if (year % four_hundred == 0) {
        return true;
    } else if (year % hundred == 0) {
        return false;
    } else if (year % 4 == 0) {
        return true;
    } else {
        return false;
    }
}
