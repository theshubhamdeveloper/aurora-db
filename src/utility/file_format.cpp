#include "utility/file_format.hpp"

#include <iostream>

namespace aurora {
    std::string FileFormat::stringify(const std::unordered_map<std::string, std::string> &data) {
        std::string output;

        for (const auto &[key, value]: data) {
            output += key + "=" + value + "\n";
        }

        return output;
    }

    std::unordered_map<std::string, std::string> FileFormat::parse(const std::string &data) {
        std::unordered_map<std::string, std::string> parsedData;

        bool separatorFound = false;

        std::string currentKey, currentValue;

        for (const auto &currentChar: data) {
            if ((currentChar == ' ' || currentChar == '\n') && !separatorFound) {
                continue;
            }

            if (currentChar == '=') {
                separatorFound = true;
                continue;
            }

            if (currentChar == '\n') {
                separatorFound = false;
                parsedData.emplace(currentKey, currentValue);
                currentKey = "";
                currentValue = "";
                continue;
            }

            if (separatorFound == true) {
                currentValue += currentChar;
            } else {
                currentKey += currentChar;
            }
        }

        return parsedData;
    }
}
