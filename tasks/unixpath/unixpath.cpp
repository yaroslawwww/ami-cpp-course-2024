#include <deque>
#include <iostream>
#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string result_path;
    std::deque<std::string> directories;
    if (path[0] == '/') {
        current_working_dir = "";
    }
    for (size_t i = 0; i < current_working_dir.size(); ++i) {
        std::string directory_name;
        while (current_working_dir[i] != '/' && i < current_working_dir.size()) {
            directory_name += current_working_dir[i];
            ++i;
        }
        if (!directory_name.empty()) {
            directories.push_back(directory_name);
        }
    }
    for (size_t i = 0; i < path.size(); ++i) {
        std::string directory_name;
        while (path[i] != '/' && i < path.size()) {
            directory_name += path[i];
            ++i;
        }
        if (directory_name == "." or directory_name.empty()) {
            continue;
        } else if (directory_name == "..") {
            if (!directories.empty()) {
                directories.pop_back();
            }
        } else {
            directories.push_back(directory_name);
        }
    }
    if (directories.empty()) {
        result_path = "/";
    }
    for (std::string_view directory : directories) {
        result_path += "/";
        result_path += directory;
    }
    return result_path;
}
