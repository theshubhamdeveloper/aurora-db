#pragma once
#include <vector>
#include <string>
#include "database_engine.hpp"

namespace aurora {
    class CLIHandler {
        CommandController *cmdController;

    public:
        explicit CLIHandler(CommandController *cmdController);

        void requestHandler(const std::string& request) const;

        static std::vector<std::string> tokenize(const std::string &data);
    };
}
