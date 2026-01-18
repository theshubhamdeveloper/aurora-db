#include "core/db_services.hpp"
#include "utility/logger.hpp"

namespace aurora {
    void DBServices::insert(const string &key, const string &value) {
        mDB.emplace(key, value);
    }

    unordered_map<string, string> DBServices::get(const string &key) const {
        if (key == "*") return mDB;

        if (!mDB.contains(key)) return {};

        return {{key, mDB.at(key)}};
    }

    void DBServices::remove(const string &key) {
        mDB.erase(key);
    }
}
