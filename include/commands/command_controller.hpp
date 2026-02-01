#pragma once
#include "commands/command.hpp"
#include "core/db_services.hpp"
#include "core/wal_handler.hpp"

namespace aurora {
    class CommandController {
        DBServices *mDBServices;
        WALHandler *mWal;

    public:
        CommandController(DBServices *dbServices, WALHandler *wal);

        void commandHandler(const Command &command) const;
    };
}
