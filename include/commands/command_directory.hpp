#pragma once
#include "core/db_services.hpp"
#include <string>

namespace aurora {
    class CommandDirectory {
        DBServices *db;

    public:
        explicit CommandDirectory(DBServices *db);

        void executeCommand(const std::string &command) const;
    };
}
