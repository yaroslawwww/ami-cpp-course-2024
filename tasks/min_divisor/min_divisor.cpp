#include "min_divisor.h"
#include "cmath"

int64_t MinDivisor(int64_t number) {
    for (int64_t i = 2; i < static_cast<int64_t>(std::sqrt(number)) + 1; ++i) {
        if (number % i == 0) {
            return i;
        }
    }
    return number;
}
