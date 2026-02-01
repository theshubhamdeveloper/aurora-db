#pragma once
#include <string>
#include "cosmos.hpp"
#include "commands/command.hpp"
#include "commands/command_action_type.hpp"

namespace aurora {
    struct WALPayload {
        CommandActionType action;
        cosmos::u32 keyLen, valueLen;
        std::string key, value;
        std::string checksum;

        [[nodiscard]] Command getCommand() const;

        static WALPayload invalid();

        static std::string stringify(const WALPayload &payload);

        static WALPayload parse(const std::string &data);
    };
}
