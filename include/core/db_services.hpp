#pragma once
#include <string>
#include <unordered_map>

using namespace std;

namespace aurora {
    class DBServices {
        unordered_map<string, string> mDB;

    public:
        void insert(const std::string &key, const std::string &value);

        unordered_map<string, string> get(const string &key) const;

        void remove(const string &key);

        void setIsRunning(bool isRunning);
    };
}
