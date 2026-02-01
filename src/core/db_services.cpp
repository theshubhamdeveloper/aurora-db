#include "core/db_services.hpp"
#include "utility/logger.hpp"

namespace aurora {
    void DBServices::insert(const std::string &key, const std::string &value) {
        mDB.emplace(key, value);
    }

    std::unordered_map<std::string, std::string> DBServices::get(const std::string &key) const {
        if (key == "*") return mDB;

        if (!mDB.contains(key)) return {};

        return {{key, mDB.at(key)}};
    }

    void DBServices::remove(const std::string &key) {
        mDB.erase(key);
    }
}
