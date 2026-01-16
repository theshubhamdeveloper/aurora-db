#pragma once
#include <iostream>
#include <string>

#include "core/cli.hpp"
using namespace crush;

namespace aurora {
    class logger {
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

        static void table(const vector<string> &cols, const vector<string> &dataCells) {
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

    private:
        static const char *prefix(Level level) {
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
