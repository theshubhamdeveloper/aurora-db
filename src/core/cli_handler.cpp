#include "core/cli_handler.hpp"
#include <iostream>
#include "utility/logger.hpp"

namespace aurora {
    CLIHandler::CLIHandler(CommandController *cmdController) : cmdController(cmdController) {
    }

    void CLIHandler::requestHandler(const std::string& request) const {
        const std::vector<std::string> cmdTokens = tokenize(request);

        const CommandActionType actionType = stringToActionType(cmdTokens[0]);

        if (actionType == CommandActionType::Invalid) {
            Logger::warn("Action type is invalid");
            return;
        }

        cmdController->commandHandler({actionType, cmdTokens[1], cmdTokens[2]});
    }


    std::vector<std::string> CLIHandler::tokenize(const std::string &data) {
        std::vector<std::string> tokens;
        bool isQuotes = false;
        std::string currentToken;

        for (const auto currentChar: data) {
            if (currentChar == '\"') {
                isQuotes = !isQuotes;
                continue;
            }

            if (currentChar == ' ' && !isQuotes) {
                tokens.push_back(currentToken);
                currentToken = "";
                continue;
            }

            currentToken += currentChar;
        }

        tokens.push_back(currentToken);
        return tokens;
    }
}
