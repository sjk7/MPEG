#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <vector>
#include <set>

#ifndef NO_ERROR
#define NO_ERROR 0
#endif

#ifndef END_OF_FILE
#define END_OF_FILE -77
#endif

#ifndef LOGIT
#define LOGIT(...) my::log_it(false, std::cout, __FILE__, __LINE__, __VA_ARGS__)
#define LOGERR(...) my::log_it(true, std::cerr, __FILE__, __LINE__, __VA_ARGS__)
#endif

namespace my {

static inline std::string now(const char* format = nullptr) {
    time_t rawtime;
    struct tm* timeinfo;
    std::string ret(128, '\0');

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (format == nullptr) {
        format = "%d/%m/%y %T";
    }

    strftime(&ret[0], 128, format, timeinfo);
    ret.resize(ret.find_first_of('\0'));
    return ret;
}

static inline std::vector<std::string_view> splitpath(
    const std::string& str, const std::set<char>& delimiters) {
    std::vector<std::string_view> result;

    char const* pch = str.c_str();
    char const* start = pch;
    for (; *pch != 0; ++pch) {
        if (delimiters.find(*pch) != delimiters.end()) {
            if (start != pch) {
                result.emplace_back(start, pch - start);
            } else {
                result.emplace_back(std::string_view());
            }
            start = pch + 1;
        }
    }
    result.emplace_back(start);

    return result;
}

std::string get_base_name(const std::string& full_path) {
#ifdef _WIN32
    std::set<char> delims{'\\'};
#else
    std::set<char> delims{'/'};
#endif

    auto splut = splitpath(full_path, delims);
    if (splut.empty()) {
        return std::string();
    }
    return std::string(splut.back());
}

template <typename W, typename... Args>
void log_it(
    bool is_error, W& where, const char* file, int line, const Args&... args) {
    using namespace std;
    const auto sep = ' ';

    where << now() << "\t";
    if (is_error) {
        where << "ERROR: ";
        where << get_base_name(file) << ":" << line << ":";
    } else {
        where << "INFO: ";
    }

    ((where << sep << args), ...);
    where << "\r\n";
}

} // namespace my
