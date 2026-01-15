#pragma once
#include <vector>
#include "db_services.hpp"
#include "commands/command_directory.hpp"

using namespace std;

namespace aurora {
    class Cli {
        CommandDirectory cd;

    public:
        explicit Cli(DBServices *db);

        void askCommand() const;

        static void printTable(vector<string> cols, vector<string> dataCells);

        static vector<string> tokenize(const string& data);
    };
}
