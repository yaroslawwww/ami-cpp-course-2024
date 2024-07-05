#include "palindrome.h"

bool IsPalindrome(const std::string &str) {
    if (str.empty()) {
        return true;
    }
    bool flag = true;
    size_t begin = 0;
    size_t end = str.length() - 1;
    while (begin < end) {
        while (str[begin] == ' ' && begin < end) {
            ++begin;
        }
        while (str[end] == ' ' && begin < end) {
            --end;
        }
        if (str[begin] != str[end] && begin < end) {
            flag = false;
        }
        if (begin == end) {
            break;
        }
        ++begin;
        --end;
    }
    return flag;
}
