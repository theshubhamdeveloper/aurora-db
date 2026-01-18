#pragma once
#include "db_services.hpp"
#include "wal_handler.hpp"
#include "commands/command_controller.hpp"

namespace aurora {
    class CommandController;

    class DatabaseEngine {
        WALHandler mWalHandler;

        DBServices mDBServices;

        CommandController mCMDController;

    public:
        DatabaseEngine();

        void start();

        void shutdown();

        WALHandler &walHandler();

        DBServices &dbServices();

        CommandController &commandController();
    };
}
