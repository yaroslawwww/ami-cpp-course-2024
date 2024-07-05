#include "search.h"

#include <algorithm>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <cctype>
#include <iostream>
#include <set>
#include <unordered_set>

bool IcharEquals(char a, char b) {
    return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b));
}

bool CompareLowerStrings(std::string_view string1, std::string_view string2) {
    return string1.size() == string2.size() and
           std::equal(string1.begin(), string1.end(), string2.begin(), IcharEquals);
}

std::vector<std::string_view> SplitStrings(std::string_view text, char separator) {
    std::vector<std::string_view> parts;
    std::string_view part;
    size_t part_begin = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == separator) {
            part = text.substr(part_begin, i - part_begin);
            part_begin = i + 1;
            if (!part.empty()) {
                parts.push_back(part);
            }
        }
    }
    part = text.substr(part_begin, text.size());
    parts.push_back(part);
    return parts;
}

std::vector<std::string_view> SplitString(std::string_view text) {
    std::vector<std::string_view> parts;
    std::string_view part;
    size_t part_begin = 0;
    for (size_t i = 0; i < text.size(); ++i) {
        if (!std::isalpha(text[i])) {
            part = text.substr(part_begin, i - part_begin);
            part_begin = i + 1;
            if (!part.empty()) {
                parts.push_back(part);
            }
        }
    }
    part = text.substr(part_begin, text.size());
    if (!part.empty()) {
        parts.push_back(part);
    }
    return parts;
}

int CountWords(std::string_view string, std::string_view word) {
    std::vector<std::string_view> words = SplitString(string);
    int counter = 0;
    for (auto i : words) {
        if (i.size() == word.size() && CompareLowerStrings(i, word)) {
            counter++;
        }
    }
    return counter;
}

double TFIDF(const std::vector<std::string_view>& strings, std::string_view string, std::string_view word) {
    int stringswithword = 0;
    for (auto s : strings) {
        if (CountWords(s, word)) {
            stringswithword++;
        }
    }
    double tf = static_cast<double>(CountWords(string, word)) / static_cast<double>(SplitString(string).size());
    double idf = log(static_cast<double>(strings.size()) / static_cast<double>(stringswithword));
    return tf * idf;
}

std::unordered_map<std::string_view, double> ALLTFIDF(const std::vector<std::string_view>& strings,
                                                      const std::unordered_set<std::string_view>& words) {
    std::unordered_map<std::string_view, double> tfidf;
    for (auto word : words) {
        for (auto string : strings) {
            tfidf[string] += TFIDF(strings, string, word);
        }
    }
    return tfidf;
}

bool CompareRelevances(const std::pair<std::string_view, double>& a, const std::pair<std::string_view, double>& b) {
    return a.second >= b.second;
}

bool IsWord(std::string_view word) {
    for (char i : word) {
        if (!std::isalpha(i)) {
            return false;
        }
    }
    return true;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<std::string_view> strings = SplitStrings(text, '\n');
    std::vector<std::string_view> words0 = SplitString(query);
    std::unordered_set<std::string_view> words;
    for (std::string_view i : words0) {
        words.emplace(i);
    }
    std::vector<std::pair<std::string_view, double>> relevances;
    std::unordered_map<std::string_view, double> temporary_relevances;
    temporary_relevances = ALLTFIDF(strings, words);
    for (std::pair<std::string_view, double> i : temporary_relevances) {
        if (i.second > 0) {
            relevances.push_back(i);
        }
    }
    std::stable_sort(relevances.begin(), relevances.end(), CompareRelevances);
    std::vector<std::string_view> result;
    for (size_t i = 0; i < std::min(results_count, relevances.size()); ++i) {
        result.push_back(relevances[i].first);
    }
    return result;
}
