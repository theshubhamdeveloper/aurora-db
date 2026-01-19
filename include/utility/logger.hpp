#pragma once
#include <iostream>
#include <string>
#include <vector>

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
            std::cout
                    << color(level)
                    << prefix(level)
                    << msg
                    << Color::Reset
                    << std::endl;
        }

        static void info(const std::string &msg) { log(Level::Info, msg); }
        static void success(const std::string &msg) { log(Level::Success, msg); }
        static void warn(const std::string &msg) { log(Level::Warn, msg); }
        static void error(const std::string &msg) { log(Level::Error, msg); }

        static void table(
            const std::vector<std::string> &columnHeaders,
            const std::vector<std::vector<std::string> > &dataCells) {
            const usize totalCols = columnHeaders.size();
            const usize totalRows = dataCells.size();

            std::vector<usize> columnWidths;
            columnWidths.reserve(totalCols);

            for (const auto &header: columnHeaders)
                columnWidths.push_back(header.size());

            // calculating cols space acquired
            for (usize r = 0; r < totalRows; r++) {
                for (usize c = 0; c < totalCols; c++) {
                    const usize cellWidth = dataCells[r][c].length();
                    if (columnWidths[c] < cellWidth)
                        columnWidths[c] = cellWidth;
                }
            }

            tableBorder(columnWidths);

            // header row
            for (usize c = 0; c < totalCols; c++) {
                std::cout << "| ";
                std::cout << columnHeaders[c];
                pad(columnWidths[c] - columnHeaders[c].size());
                std::cout << " ";
            }
            std::cout << "|" << std::endl;

            tableBorder(columnWidths);

            // body rows
            for (usize r = 0; r < totalRows; r++) {
                for (usize c = 0; c < totalCols; c++) {
                    std::cout << "| ";
                    std::cout << dataCells[r][c];
                    pad(columnWidths[c] - dataCells[r][c].size());
                    std::cout << " ";
                }
                std::cout << "|" << std::endl;
            }

            tableBorder(columnWidths);
        }

    private:
        struct Color {
            static constexpr auto Reset = "\033[0m";
            static constexpr auto Gray = "\033[90m";
            static constexpr auto Green = "\033[32m";
            static constexpr auto Yellow = "\033[33m";
            static constexpr auto Red = "\033[31m";
        };

        static const char *color(const Level level) {
            switch (level) {
                case Level::Info: return Color::Gray;
                case Level::Success: return Color::Green;
                case Level::Warn: return Color::Yellow;
                case Level::Error: return Color::Red;
            }
            return Color::Reset;
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

        static void tableBorder(const std::vector<usize> &columnWidths) {
            for (const usize w: columnWidths) {
                std::cout << "+";
                for (usize i = 0; i < w + 2; i++)
                    std::cout << "-";
            }
            std::cout << "+" << std::endl;
        }

        static void pad(const usize count) {
            for (usize i = 0; i < count; i++)
                std::cout << " ";
        }
    };
}
