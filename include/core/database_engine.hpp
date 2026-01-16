#pragma once
#include "db_services.hpp"
#include "wal_handler.hpp"
#include "commands/command_controller.hpp"

namespace aurora {
    class CommandController;

    class DatabaseEngine {
        DBServices mDBServices;

        CommandController mCMDController;

    public:
        DatabaseEngine();

        void start();

        void shutdown();

        DBServices &dbServices();

        CommandController &commandController();
    };
}
