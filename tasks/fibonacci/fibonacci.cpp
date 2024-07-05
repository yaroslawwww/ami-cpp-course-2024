#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t first_fibonacci = 0;
    int64_t second_fibonacci = 1;
    for (std::size_t i = 0; i < n; ++i) {
        int64_t temp = first_fibonacci + second_fibonacci;
        first_fibonacci = second_fibonacci;
        second_fibonacci = temp;
    }
    return first_fibonacci;
}
