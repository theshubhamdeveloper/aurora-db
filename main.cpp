#include "core/db_services.hpp"
#include "library/data_type.hpp"
#include <iostream>

#include "core/cli.hpp"

using namespace crush;
using namespace aurora;
using namespace std;

i32 main() {
    auto dbManager = DBServices();
    auto cli = Cli(&dbManager);
    string cmd;

    cout << std::endl;
    cout << "------ Welcome to AuroraDB! ------" << std::endl;
    cout << std::endl;
    cout << "- Perform your action -";
    cout << std::endl;

    while (dbManager.getIsRunning()) {
        cout << "auroraDB> ";
        cli.askCommand();
    }

    return 0;
}
