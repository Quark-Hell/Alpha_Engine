#include "Parser.h"

#include <iostream>
#include <regex>
#include <fstream>

std::vector<std::filesystem::path> Parser::FindHeaderFiles(const std::vector<std::filesystem::path>& dirs) {
    std::vector<std::filesystem::path> headers;
    for (auto& dir : dirs) {
        if (!std::filesystem::exists(dir)) {
            std::cout << "Directory doesn't exist: " << dir << std::endl;
            continue;
        }

        for (auto& p : std::filesystem::recursive_directory_iterator(dir)) {
            if (!p.is_regular_file()) continue;

            // Skip any path that contains "External"
            if (p.path().string().find("External") != std::string::npos)
                continue;

            if (p.path().extension() == ".h" || p.path().extension() == ".hpp") {
                headers.push_back(p.path());
                std::cout << "Found header: " << p.path() << std::endl;
            }
        }
    }
    return headers;
}


std::string Parser::ReadFileToString(const std::filesystem::path& file) {
    std::ifstream in(file);
    if (!in.is_open()) {
        std::cout << "Failed to open file: " << file << std::endl;
        return {};
    }
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

std::string Parser::PreprocessCode(const std::string& code) {
    std::string result = code;
    // remove single-line comments
    result = std::regex_replace(result, std::regex(R"(//.*)"), "");
    // remove multi-line comments
    result = std::regex_replace(result, std::regex(R"(/\*[\s\S]*?\*/)"), "");

    return result;
}


bool Parser::ShouldExcludeClass(const std::string& parentName) {
    static const std::unordered_set<std::string> excludedBases = {
        "TSystemData",
        "Core::TSystemData",
        "SystemData",
        "Core::SystemData"
    };

    // Check if exactly equal
    if (excludedBases.count(parentName)) {
        return true;
    }

    // Check template classes (например, TSystemData<T>)
    for (const auto& excluded : excludedBases) {
        if (parentName.find(excluded + "<") == 0) {
            return true;
        }
        // Check witout namespace
        size_t pos = excluded.find_last_of(':');
        if (pos != std::string::npos && pos + 1 < excluded.length()) {
            std::string shortExcluded = excluded.substr(pos + 1);
            if (parentName.find(shortExcluded + "<") == 0) {
                return true;
            }
        }
    }

    return false;
}


std::unordered_set<std::string> Parser::ParseCode (
    const std::string& code,
    const std::unordered_set<std::string>& baseClasses
) {
    std::unordered_set<std::string> foundClasses;

    std::regex classRegex(R"((class|struct)\s+(\w+)(?:\s+final)?\s*:\s*([^{]+)\{)");

    std::smatch match;
    std::string::const_iterator searchStart(code.cbegin());

    while (std::regex_search(searchStart, code.cend(), match, classRegex)) {
        std::string className = match[2];
        std::string bases = match[3]; 

        std::cout << "Found class: " << className << " with bases: " << bases << std::endl;

        // Check inheritance from excluded classes
        bool isExcluded = false;
        std::regex baseSplit(R"((?:public|protected|private)?\s*([\w:<>]+))");
        auto bases_begin = std::sregex_iterator(bases.begin(), bases.end(), baseSplit);
        auto bases_end = std::sregex_iterator();

        for (auto it = bases_begin; it != bases_end; ++it) {
            std::string parentName = (*it)[1].str();
            if (ShouldExcludeClass(parentName)) {
                std::cout << "  -> Excluded due to non-component base: " << parentName << std::endl;
                isExcluded = true;
                break;
            }
        }

        if (isExcluded) {
            searchStart = match.suffix().first;
            continue;
        }

        // Check matches with classes
        bases_begin = std::sregex_iterator(bases.begin(), bases.end(), baseSplit);
        for (auto it = bases_begin; it != bases_end; ++it) {
            std::string parentName = (*it)[1].str();
            std::cout << "  Checking parent: " << parentName << std::endl;

            bool found = false;
            if (baseClasses.count(parentName)) {
                found = true;
            }
            else {
                // Check name without namespace (example, Core::Component -> Component)
                size_t pos = parentName.find_last_of(':');
                if (pos != std::string::npos && pos + 1 < parentName.length()) {
                    std::string shortName = parentName.substr(pos + 1);
                    if (baseClasses.count(shortName)) {
                        found = true;
                    }
                }
            }

            if (found) {
                std::cout << "  -> Match found! Adding " << className << std::endl;
                foundClasses.insert(className);
                break; // only need one matching base
            }
        }

        searchStart = match.suffix().first;
    }

    return foundClasses;
}


std::unordered_set<std::string> Parser::ParseHeaders (
    const std::vector<std::filesystem::path>& headers,
    const std::unordered_set<std::string>& baseClasses
) {
    std::unordered_set<std::string> foundClasses;

    std::cout << "Parsing " << headers.size() << " header files..." << std::endl;
    std::cout << "Looking for classes inheriting from: ";
    for (const auto& base : baseClasses) {
        std::cout << base << " ";
    }
    std::cout << std::endl;

    for (auto& file : headers) {
        std::cout << "Processing: " << file << std::endl;
        std::string code = ReadFileToString(file);
        if (code.empty()) continue;

        code = PreprocessCode(code);
        auto newClasses = ParseCode(code, baseClasses);
        foundClasses.insert(newClasses.begin(), newClasses.end());
    }
    return foundClasses;
}