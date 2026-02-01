#pragma once
#include <string>
#include <unordered_map>

namespace aurora {
    class DBServices {
        std::unordered_map<std::string, std::string> mDB;

    public:
        void insert(const std::string &key, const std::string &value);

        [[nodiscard]] std::unordered_map<std::string, std::string> get(const std::string &key) const;

        void remove(const std::string &key);
    };
}
