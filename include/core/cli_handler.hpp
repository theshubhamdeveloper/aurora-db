#pragma once
#include <vector>

#include "database_engine.hpp"

using namespace std;

namespace aurora {
    class CLIHandler {
        CommandController *cmdController;

    public:
        explicit CLIHandler(CommandController *cmdController);

        void requestHandler(const string& request) const;

        static vector<string> tokenize(const string &data);
    };
}
