#include "commands/command_controller.hpp"
#include "utility/logger.hpp"

namespace aurora {
    CommandController::CommandController(DBServices *dbServices,
                                         WALHandler *wal) : mDBServices(dbServices), mWal(wal) {
    }

    void CommandController::commandHandler(const Command &command) const {
        switch (command.action) {
            case CommandActionType::Insert:
                mWal->append(command);
                mDBServices->insert(command.key, command.value);
                break;

            case CommandActionType::Get: {
                std::vector<std::vector<std::string> > table;

                const std::unordered_map<std::string, std::string> data = mDBServices->get(command.key);

                if (data.empty()) {
                    Logger::info("Key does not exits");
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
                mWal->append(command);
                mDBServices->remove(command.key);
                break;

            default:
                break;
        }
    }
}
