#include "core/database_engine.hpp"

#include "utility/logger.hpp"

namespace aurora {
    DatabaseEngine::DatabaseEngine() : mCMDController(&mDBServices) {
    }

    void DatabaseEngine::start() {
        Logger::info("Starting database engine...");
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
}
