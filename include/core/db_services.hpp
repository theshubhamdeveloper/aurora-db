#pragma once
#include <string>
#include <unordered_map>

namespace aurora {
    class DBServices {
        std::unordered_map<std::string, std::string> mDB;
        bool mIsRunning;

    public:
        DBServices();

        void insert(const std::string &key, const std::string &value);

        [[nodiscard]] std::string find(const std::string &key) const;

        void remove(const std::string &key);

        void setIsRunning(bool isRunning);

        [[nodiscard]] bool getIsRunning() const;

        [[nodiscard]] const std::unordered_map<std::string, std::string> &getData() const;
    };
}
