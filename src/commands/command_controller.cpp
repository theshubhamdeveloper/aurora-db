#include "commands/command_controller.hpp"

#include "utility/logger.hpp"

namespace aurora {
    CommandController::CommandController(DBServices *dbServices) : mDBServices(dbServices) {
    }

    void CommandController::commandHandler(const Command &command) const {
        switch (command.action) {
            case CommandActionType::Insert:
                mDBServices->insert(command.key, command.value);
                break;

            case CommandActionType::Get: {
                vector<vector<string> > table;

                const unordered_map<string, string> data = mDBServices->get(command.key);

                if (data.empty()) {
                    Logger::info("Database is empty");
                    break;
                }

                table.reserve(data.size());
                for (const auto &[key, value]: data) {
                    table.push_back({key, value});
                }

                Logger::table({"Key", "Value"}, table);
            }
            break;

            case CommandActionType::Remove:
                mDBServices->remove(command.key);
                break;

            default:
                break;
        }
    }
}
