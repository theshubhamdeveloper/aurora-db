#pragma once
#include <iostream>
#include <string>

#include "core/cli_handler.hpp"
using namespace crush;

namespace aurora {
    class Logger {
    public:
        enum class Level {
            Info,
            Success,
            Warn,
            Error,
        };

        static void log(const Level level, const std::string &msg) {
            std::cout << prefix(level) << msg << std::endl;
        }

        static void info(const std::string &msg) { log(Level::Info, msg); }
        static void success(const std::string &msg) { log(Level::Success, msg); }
        static void warn(const std::string &msg) { log(Level::Warn, msg); }
        static void error(const std::string &msg) { log(Level::Error, msg); }

        static void table(const vector<string> &columnHeaders, const vector<vector<string> > &dataCells) {
            const usize totalCols = columnHeaders.size();
            const usize totalRows = dataCells.size();

            vector<usize> columnWidths;
            columnWidths.reserve(columnHeaders.size());

            for (const auto& header : columnHeaders) {
                columnWidths.push_back(header.size());
            }

            // calculating cols space acquired
            for (usize r = 0; r < totalRows; r++) {
                for (usize c = 0; c < totalCols; c++) {
                    const usize cellWidth = dataCells[r][c].length();
                    if (columnWidths[c] < cellWidth)
                        columnWidths[c] = cellWidth;
                }
            }

            //printing table col headers
            tableBorder(columnWidths);

            for (usize c = 0; c < totalCols; c++) {
                cout << "|";

                const string &header = columnHeaders[c];
                cout << " " << header << " ";

                for (usize k = 0; k < columnWidths[c] - header.size(); k++) {
                    cout << " ";
                }
            }
            cout << "|" << endl;

            tableBorder(columnWidths);

            //printing table body
            for (usize r = 0; r < totalRows; r++) {
                for (usize c = 0; c < totalCols; c++) {
                    cout << "|";

                    const string &cell = dataCells[r][c];
                    cout << " " << cell << " ";

                    for (usize k = 0; k < columnWidths[c] - cell.size(); k++) {
                        cout << " ";
                    }
                }
                cout << "|" << endl;
            }

            tableBorder(columnWidths);
        }

    private:
        static void tableBorder(const vector<usize> &columnWidths) {
            for (const usize &columnWidth: columnWidths) {
                cout << "+";
                for (usize k = 0; k < columnWidth + 2; k++) {
                    cout << "-";
                }
            }
            cout << "+" << endl;
        }

        static const char *prefix(const Level level) {
            switch (level) {
                case Level::Info: return "[INFO] ";
                case Level::Success: return "[OK] ";
                case Level::Warn: return "[WARN] ";
                case Level::Error: return "[ERROR] ";
            }
            return "";
        }
    };
}
