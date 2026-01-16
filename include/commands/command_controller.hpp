#pragma once

#include "commands/command.hpp"
#include "core/db_services.hpp"
#include "core/wal_handler.hpp"

namespace aurora {
    class CommandController {
        DBServices *mDBServices;

    public:
        CommandController(DBServices *dbServices);

        void commandHandler(const Command &command) const;
    };
}
