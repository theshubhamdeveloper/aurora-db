#include "core/db_services.hpp"
#include "library/data_type.hpp"
#include <iostream>

#include "core/cli_handler.hpp"

using namespace crush;
using namespace aurora;
using namespace std;

i32 main() {
    auto dbEngine = DatabaseEngine();

    const auto cli = CLIHandler(&dbEngine.commandController());

    bool isRunning = true;

    dbEngine.start();

    cout << "\n" << "------ Welcome to AuroraDB! ------" << "\n" << "\n";

    while (isRunning) {
        string input;

        cout << "AuroraDB > ";
        getline(cin, input);

        if (input == "exit") {
            isRunning = false;
            continue;
        }

        cli.requestHandler(input);
    }

    dbEngine.shutdown();

    cout << "\n" << "------ Thanks for using AuroraDB! ------" << "\n";

    return 0;
}
