#pragma once
#include <string>
#include <unordered_map>

namespace aurora {
    class FileFormat {
    public:
        static std::string stringify(const std::unordered_map<std::string, std::string> &data);

        static std::unordered_map<std::string, std::string> parse(const std::string &data);
    };
}
