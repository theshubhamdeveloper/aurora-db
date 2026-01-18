#pragma once
#include <string>

#include "commands/command.hpp"
#include "commands/command_action_type.hpp"

using namespace std;

namespace aurora {
    struct WALPayload {
        CommandActionType action;
        u32 keyLen, valueLen;
        string key, value;
        string checksum;

        [[nodiscard]] Command getCommand() const;

        static WALPayload invalid();

        static string stringify(const WALPayload &payload);

        static WALPayload parse(const string &data);
    };
}
