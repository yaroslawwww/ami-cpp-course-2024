#include "password.h"

bool ValidatePassword(const std::string &password) {
    const uint64_t max_length = 14;
    const uint64_t min_length = 8;
    const char max_symbol = '~';
    const char min_symbol = '!';
    const char max_cap_letter = 'Z';
    const char min_cap_letter = 'A';
    const char max_low_letter = 'z';
    const char min_low_letter = 'a';
    const char max_number = '9';
    const char min_number = '0';
    if (password.length() > max_length || password.length() < min_length) {
        return false;
    }
    uint contains_capital_letters = 0;
    uint contains_lowercase_letters = 0;
    uint contains_numbers = 0;
    uint contains_other = 0;
    for (size_t i = 0; i < password.length(); ++i) {
        char symbol = password[i];
        if (symbol > max_symbol || symbol < min_symbol) {
            return false;
        } else if (min_cap_letter <= symbol && symbol <= max_cap_letter) {
            contains_capital_letters = 1;
        } else if (min_low_letter <= symbol && symbol <= max_low_letter) {
            contains_lowercase_letters = 1;
        } else if (min_number <= symbol && symbol <= max_number) {
            contains_numbers = 1;
        } else {
            contains_other = 1;
        }
    }
    if (contains_capital_letters + contains_lowercase_letters + contains_numbers + contains_other >= 3) {
        return true;
    }
    return false;
}
