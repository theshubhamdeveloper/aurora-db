#include "core/database_engine.hpp"
#include "utility/logger.hpp"

namespace aurora {
    DatabaseEngine::DatabaseEngine() : mWalHandler(&mDBServices, "aurora.wal"),
                                       mCMDController({&mDBServices, &mWalHandler}) {
    }

    void DatabaseEngine::start() {
        Logger::info("Starting database engine...");
        mWalHandler.replay();
    }

    void DatabaseEngine::shutdown() {
        Logger::info("Shutting down database engine...");
    }


    CommandController &DatabaseEngine::commandController() {
        return mCMDController;
    }

    DBServices &DatabaseEngine::dbServices() {
        return mDBServices;
    }

    WALHandler &DatabaseEngine::walHandler() {
        return mWalHandler;
    }
}
