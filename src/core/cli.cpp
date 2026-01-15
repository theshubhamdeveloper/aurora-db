#include "core/cli.hpp"
#include <iostream>

#include "library/data_type.hpp"

using namespace crush;

namespace aurora {
    Cli::Cli(DBServices *db) : cd(db) {
    }

    void Cli::askCommand() const {
        string input;
        getline(cin, input);
        cd.executeCommand(input);
    }

    vector<string> Cli::tokenize(const string &data) {
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

    void Cli::printTable(vector<string> cols, vector<string> dataCells) {
        const i32 colsSize = cols.size();
        const i32 dataCellsSize = dataCells.size();

        i32 colWidths[colsSize];
        for (i32 i = 0; i < colsSize; i++) {
            colWidths[i] = cols[i].size();
        }

        for (i32 i = 0; i < dataCellsSize; i++) {
            const i32 cellWidth = dataCells[i].length();
            const i32 colIndex = i % colsSize;

            if (colWidths[colIndex] < cellWidth)
                colWidths[colIndex] = cellWidth;
        }

        //header
        for (i32 i = 0; i < colsSize; i++) {
            cout << "+";
            const i32 colIndex = i % colsSize;
            for (i32 k = 0; k < colWidths[colIndex] + 2; k++) {
                cout << "-";
            }
        }
        cout << "+" << endl;
        for (i32 i = 0; i < colsSize; i++) {
            cout << "|";
            const string &col = cols[i];
            cout << " " << col << " ";
            for (i32 k = 0; k < colWidths[i] - col.size(); k++) {
                cout << " ";
            }
        }
        cout << "|" << endl;
        for (i32 i = 0; i < colsSize; i++) {
            cout << "+";
            const i32 colIndex = i % colsSize;
            for (i32 k = 0; k < colWidths[colIndex] + 2; k++) {
                cout << "-";
            }
        }
        cout << "+" << endl;


        //body
        for (i32 i = 0; i < dataCellsSize / colsSize; i++) {
            for (i32 j = 0; j < colsSize; j++) {
                cout << "|";
                const string &cell = dataCells[i * colsSize + j];
                cout << " " << cell << " ";
                for (i32 k = 0; k < colWidths[j] - cell.size(); k++) {
                    cout << " ";
                }
            }
            cout << "|" << endl;
        }
        for (i32 i = 0; i < colsSize; i++) {
            cout << "+";
            const i32 colIndex = i % colsSize;
            for (i32 k = 0; k < colWidths[colIndex] + 2; k++) {
                cout << "-";
            }
        }
        cout << "+" << endl;
    }
}
