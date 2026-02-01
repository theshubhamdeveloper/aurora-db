#include "core/wal_handler.hpp"
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include "core/wal_payload.hpp"
#include "utility/logger.hpp"

namespace aurora {
    WALHandler::WALHandler(DBServices *dbServices, const std::string &fileName) : mDBServices(dbServices),
                                                                             mFileName(fileName),
                                                                             mPermissions(S_IRUSR | S_IWUSR) {
        mWalFd = open(fileName.data(), O_CREAT | O_WRONLY | O_APPEND, mPermissions);
        if (mWalFd < 0) {
            Logger::error("Error opening file");
        }
    }

    WALHandler::~WALHandler() {
        close(mWalFd);
    }

    void WALHandler::append(const Command &command) const {
        WALPayload payload = {
            command.action, static_cast<cosmos::u32>(command.key.length()),
            static_cast<cosmos::u32>(command.value.length()),
            command.key, command.value
        };

        payload.checksum = std::to_string(generateChecksum(command));

        const std::string entry = WALPayload::stringify(payload);

        write(mWalFd, entry.data(), entry.size());
        fsync(mWalFd);
    }

    bool WALHandler::applyReplayInDB(const WALPayload &payload) const {
        if (!validatePayload(payload)) {
            Logger::error("Invalid WAL payload: " + WALPayload::stringify(payload));
            return false;
        }

        if (payload.action == CommandActionType::Insert) {
            mDBServices->insert(payload.key, payload.value);
        } else if (payload.action == CommandActionType::Remove) {
            mDBServices->remove(payload.key);
        }

        return true;
    }


    void WALHandler::replay() const {
        const cosmos::i32 fd = open(mFileName.data(), O_CREAT | O_RDONLY, mPermissions);
        if (fd < 0) {
            Logger::error("Error opening file");
        }

        constexpr cosmos::u16 BUFFER_LEN = 256;
        std::string currentPayload;
        char buffer[BUFFER_LEN];

        cosmos::isize readLength;
        do {
            readLength = read(fd, buffer, BUFFER_LEN);
            for (cosmos::isize i = 0; i < readLength; ++i) {
                if (buffer[i] == '\n') {
                    if (!applyReplayInDB(WALPayload::parse(currentPayload))) return;
                    currentPayload = "";
                    continue;
                }

                currentPayload += buffer[i];
            }
        } while (readLength == BUFFER_LEN);

        close(fd);
    }

    cosmos::u8 WALHandler::generateChecksum(const Command &command) {
        std::string commandPayload = std::to_string(command.key.length()) + command.key;
        if (!command.value.empty()) {
            commandPayload = std::to_string(command.value.length()) + command.value;
        }

        cosmos::u8 cs = 0;
        for (const char c: commandPayload) {
            cs ^= c;
        }
        return cs;
    }

    bool WALHandler::validatePayload(const WALPayload &payload) {
        if (payload.action == CommandActionType::Invalid)
            return false;

        if (payload.key.length() != payload.keyLen || payload.value.length() != payload.valueLen)
            return false;

        if (std::to_string(generateChecksum(payload.getCommand())) != payload.checksum)
            return false;

        return true;
    }
}
