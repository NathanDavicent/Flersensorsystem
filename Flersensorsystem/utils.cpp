#include "utils.h"
#include <ctime>
#include <cctype>

std::string nowTimestamp() {
    std::time_t t = std::time(nullptr);
    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &t);     // Windows
#else
    localtime_r(&t, &tm);     // Linux/macOS
#endif
    char buf[20];             // "YYYY-MM-DD HH:MM" = 16 tecken + \0
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", &tm);
    return std::string(buf);
}

static std::string ltrim(const std::string& s) {
    size_t i = 0;
    while (i < s.size() && std::isspace((unsigned char)s[i])) ++i;
    return s.substr(i);
}

static std::string rtrim(const std::string& s) {
    if (s.empty()) return s;
    size_t i = s.size();
    while (i > 0 && std::isspace((unsigned char)s[i - 1])) --i;
    return s.substr(0, i);
}

std::string trim(const std::string& s) {
    return rtrim(ltrim(s));
}

std::vector<std::string> splitCsvSimple(const std::string& line) {
    // Delar bara på ',' och trimmar varje del. Hanterar inte citattecken.
    std::vector<std::string> parts;
    std::string cur;
    for (char c : line) {
        if (c == ',') {
            parts.push_back(trim(cur));
            cur.clear();
        }
        else {
            cur.push_back(c);
        }
    }
    parts.push_back(trim(cur));
    return parts;
}
