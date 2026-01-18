#pragma once
#include <string>

#include "db_services.hpp"
#include "wal_payload.hpp"
#include "commands/command.hpp"
#include "library/data_type.hpp"

using namespace std;

namespace aurora {
    class WALHandler {
        DBServices *mDBServices;
        string mFileName;
        i32 mWalFd;
        u16 mPermissions;

    public:
        explicit WALHandler(DBServices *dbServices, const string &fileName);

        ~WALHandler();

        void append(const Command &command) const;

        void replay() const;

        bool applyReplayInDB(const WALPayload &payload) const;

        static bool validatePayload(const WALPayload &payload);

        static u8 generateChecksum(const Command &command);
    };
}
