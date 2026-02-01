#pragma once
#include <string>
#include "command_action_type.hpp"

namespace aurora {
    struct Command {
        CommandActionType action;
        std::string key;
        std::string value;
    };
}
