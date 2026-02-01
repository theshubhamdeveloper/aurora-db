#pragma once
#include <string>
#include "cosmos.hpp"
#include "db_services.hpp"
#include "wal_payload.hpp"
#include "commands/command.hpp"

namespace aurora {
    class WALHandler {
        DBServices *mDBServices;
        std::string mFileName;
        cosmos::i32 mWalFd;
        cosmos::u16 mPermissions;

    public:
        explicit WALHandler(DBServices *dbServices, const std::string &fileName);

        ~WALHandler();

        void append(const Command &command) const;

        void replay() const;

        [[nodiscard]] bool applyReplayInDB(const WALPayload &payload) const;

        static bool validatePayload(const WALPayload &payload);

        static cosmos::u8 generateChecksum(const Command &command);
    };
}
