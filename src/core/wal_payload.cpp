#include "core/wal_payload.hpp"
#include <vector>

#include "utility/logger.hpp"

namespace aurora {
    Command WALPayload::getCommand() const {
        return {action, key, value};
    }

    string WALPayload::stringify(const WALPayload &payload) {
        string payloadStr = actionTypeToString(payload.action, true) +
                            "|" + to_string(payload.keyLen) +
                            "|" + payload.key;

        if (!payload.value.empty()) {
            payloadStr += "|" + to_string(payload.value.length()) + "|" + payload.value;
        }

        payloadStr += "|" + payload.checksum +
                +"\n";

        return payloadStr;
    }

    WALPayload WALPayload::parse(const string &data) {
        string current;
        vector<string> tokens;

        for (const char currentChar: data) {
            if (currentChar == '|') {
                tokens.push_back(current);
                current = "";
                continue;
            }
            current += currentChar;
        }
        tokens.push_back(current);

        const CommandActionType action = stringToActionType(tokens[0]);
        if (action == CommandActionType::Invalid) {
            Logger::error("Invalid command action type");
            return invalid();
        }

        const u32 keyLen = stoi(tokens[1]);
        const string key = tokens[2];

        if (action != CommandActionType::Insert) {
            return {action, keyLen, 0, key, "", tokens[3]};
        }

        const u32 valueLen = stoi(tokens[3]);
        const string value = tokens[4];

        return {action, keyLen, valueLen, key, value, tokens[5]};
    }

    WALPayload WALPayload::invalid() {
        return {CommandActionType::Invalid, 0, 0, "", ""};
    }
}
