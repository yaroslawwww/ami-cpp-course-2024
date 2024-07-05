#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    bool is_positive = (0 < slices_amount);
    bool is_not_big = (slices_amount < height * width);
    bool break_along = (slices_amount % height == 0);
    bool break_across = (slices_amount % width == 0);
    return is_positive && is_not_big && (break_along || break_across);
}
