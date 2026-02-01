#include "include/cosmos.hpp"
#include <iostream>
#include "algorithm/btree.hpp"
#include "core/cli_handler.hpp"

cosmos::i32 main() {
    auto dbEngine = aurora::DatabaseEngine();

    const auto cli = aurora::CLIHandler(&dbEngine.commandController());

    bool isRunning = true;

    dbEngine.start();

    std::cout << "\n" << "------ Welcome to AuroraDB! ------" << "\n" << "\n";

    while (isRunning) {
        std::string input;

        std::cout << "AuroraDB > ";
        getline(std::cin, input);

        if (input == "exit") {
            isRunning = false;
            continue;
        }

        cli.requestHandler(input);
    }

    dbEngine.shutdown();

    std::cout << "\n" << "------ Thanks for using AuroraDB! ------" << "\n";

    return 0;
}
