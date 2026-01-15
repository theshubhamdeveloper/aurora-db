#include "core/db_services.hpp"
#include <iostream>
#include <ostream>

namespace aurora {
    DBServices::DBServices() : mIsRunning(true) {
    }

    void DBServices::insert(const std::string &key, const std::string &value) {
        mDB.insert({key, value});
    }

    std::string DBServices::find(const std::string &key) const { return mDB.at(key); }

    void DBServices::remove(const std::string &key) {
        mDB.erase(key);
    }

    void DBServices::setIsRunning(const bool isRunning) {
        mIsRunning = isRunning;
    }

    bool DBServices::getIsRunning() const {
        return mIsRunning;
    }

    const std::unordered_map<std::string, std::string> &DBServices::getData() const {
        return mDB;
    }
}
