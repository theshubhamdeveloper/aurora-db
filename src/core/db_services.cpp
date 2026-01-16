#include "core/db_services.hpp"
#include <iostream>
#include <ostream>

namespace aurora {
    void DBServices::insert(const string &key, const string &value) {
        mDB.emplace(key, value);
    }

    unordered_map<string, string> DBServices::get(const string &key) const {
        if (key == "*") {
            return mDB;
        }
        return {{key, mDB.at(key)}};
    }

    void DBServices::remove(const string &key) {
        mDB.erase(key);
    }
}
