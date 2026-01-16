#include "core/cli_handler.hpp"
#include <iostream>

#include "library/data_type.hpp"
#include "utility/logger.hpp"

using namespace crush;

namespace aurora {
    CLIHandler::CLIHandler(CommandController *cmdController) : cmdController(cmdController) {
    }

    void CLIHandler::requestHandler(const string& request) const {
        const vector<string> cmdTokens = tokenize(request);

        const CommandActionType actionType = stringToActionType(cmdTokens[0]);

        if (actionType == CommandActionType::Invalid) {
            Logger::warn("Action type is invalid");
            return;
        }

        cmdController->commandHandler({actionType, cmdTokens[1], cmdTokens[2]});
    }


    vector<string> CLIHandler::tokenize(const string &data) {
        vector<string> tokens;
        bool isQuotes = false;
        string currentToken;

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
