#include <numeric>
#include "reduce_fraction.h"

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t greatest_common_divisor = std::gcd(numerator, denominator);
    return (numerator + denominator) / greatest_common_divisor;
}
