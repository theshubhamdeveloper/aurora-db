#pragma once
#include <string>
#include <algorithm>
#include <ranges>

#include "library/data_type.hpp"

using namespace std;
using namespace crush;

namespace aurora {
    enum class CommandActionType {
        Insert,
        Get,
        Update,
        Remove,
        Invalid = 999,
    };

    inline string actionTypeToString(const CommandActionType action, const bool toUppercase = false) {
        string actionStr;
        switch (action) {
            case CommandActionType::Insert:
                actionStr = "insert";
                break;
            case CommandActionType::Get:
                actionStr = "get";
                break;
            case CommandActionType::Update:
                actionStr = "update";
                break;
            case CommandActionType::Remove:
                actionStr = "remove";
                break;
            default:
                actionStr = "invalid";
                break;
        }

        if (toUppercase)
            ranges::transform(actionStr,
                              actionStr.begin(),
                              [](const u8 c) {
                                  return static_cast<char>(toupper(c));
                              });

        return actionStr;
    }

    inline CommandActionType stringToActionType(string actionStr) {
        ranges::transform(actionStr,
                          actionStr.begin(),
                          [](const u8 c) {
                              return static_cast<char>(tolower(c));
                          });

        if (actionStr == "insert")
            return CommandActionType::Insert;
        if (actionStr == "get")
            return CommandActionType::Get;
        if (actionStr == "update")
            return CommandActionType::Update;
        if (actionStr == "remove")
            return CommandActionType::Remove;

        return CommandActionType::Invalid;
    }
}
