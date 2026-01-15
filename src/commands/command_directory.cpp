#include "commands/command_directory.hpp"

#include <iostream>
#include <ostream>

#include "core/cli.hpp"
#include "library/data_type.hpp"

namespace aurora {
    CommandDirectory::CommandDirectory(DBServices *db) : db(db) {
    }

    void CommandDirectory::executeCommand(const std::string &command) const {
        auto tokens = Cli::tokenize(command);

        crush::i32 tokenSize = tokens.size();

        if (tokens[0] == "exit")
            db->setIsRunning(false);

        else if (tokens[0] == "insert" && tokenSize == 3)
            db->insert(tokens[1], tokens[2]);

        else if (tokens[0] == "remove" && tokenSize == 2)
            db->remove(tokens[1]);

        else if (tokens[0] == "find" && tokenSize == 2)
            Cli::printTable({"Key", "Value"}, {tokens[1], db->find(tokens[1])});

        else if (tokens[0] == "show" && tokenSize == 2) {
            if (tokens[1] == "database") {
                std::vector<std::string> dataCells;
                for (const auto &[key, value]: db->getData()) {
                    dataCells.push_back(key);
                    dataCells.push_back(value);
                }

                Cli::printTable({"Key", "Value"}, dataCells);
            }
        }
    }
}
