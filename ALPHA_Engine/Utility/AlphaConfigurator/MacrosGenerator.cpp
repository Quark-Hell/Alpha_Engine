#include "MacrosGenerator.h"
#include <regex>

namespace Utility {

    std::list<std::string> MacrosGenerator::ExtractBaseClasses(const std::string& str) {
        const std::regex baseClassPattern(R"(\S+)");

        std::smatch match;
        std::list<std::string> baseClasses;

        auto it = str.begin();
        while (std::regex_search(it, str.end(), match, baseClassPattern)) {
            baseClasses.push_back(match[0].str());
            it = match[0].second;
        }

        bool foundColon = false;
        auto line = baseClasses.begin();
        for (; line != baseClasses.end(); ++line) {
            if (*line == ":") {
                foundColon = true;
                line = baseClasses.erase(line);
                --line;
                continue;
            }
            if (foundColon == false) {
                line = baseClasses.erase(line);
                --line;
                continue;
            }
            if (*line == "public" || *line == "private" || *line == "protected" || *line == ",") {
                line = baseClasses.erase(line);
                --line;
                continue;
            }
            if (*line == "{") {
                line = baseClasses.erase(line, baseClasses.end());
                --line;
                continue;
            }
        }

        return baseClasses;
    }

    void MacrosGenerator::GenerateSerializeMacros(const std::string& className, std::list<std::string>& baseClasses, File& output) {
        std::string name = className;
        std::transform(name.begin(), name.end(), name.begin(), ::toupper);

        output._generatedBuffer.emplace_back("");
        output._generatedBuffer.emplace_back("#define SERIALIZE_" + name + "(...)\t\t\\");
        output._generatedBuffer.emplace_back("friend bitsery::Access;\t\t\\");
        output._generatedBuffer.emplace_back("template <typename BIT>\t\t\\");
        output._generatedBuffer.emplace_back("void serialize(BIT& ser) {\t\t\\");

        for (auto it = baseClasses.begin(); it != baseClasses.end(); ++it) {
            if (*it == "virtual") {
                std::advance(it, 1);
                const std::string& derived = *it;
                std::string stroke = "ser.ext(*this, bitsery::ext::VirtualBaseClass<" + derived + ">{});";
                output._generatedBuffer.emplace_back(stroke + "\t\t\\");
            }
            else {
                const std::string& derived = *it;
                std::string stroke = "ser.ext(*this, bitsery::ext::BaseClass<" + derived + ">{});";
                output._generatedBuffer.emplace_back(stroke + "\t\t\\");
            }
        }

        output._generatedBuffer.emplace_back("ser(__VA_ARGS__);\t\t\\");
        output._generatedBuffer.emplace_back("}");
        output._generatedBuffer.emplace_back("");
    }

    void MacrosGenerator::ACLASS(std::vector<File> &files) {
        bool findMacros = false;

        const std::regex classPattern(R"(struct|class\s+([A-Za-z_][A-Za-z0-9_]*)\s*)");
        std::smatch match;

        for (auto& cfg : files) {
            if (cfg.GetSourceName().find(".generated") != std::string::npos) {continue;}
            cfg._generatedBuffer.emplace_back("#define ACLASS()");

            for (auto& line : cfg._sourceBuffer) {
                if (line.find("ACLASS()") != std::string::npos) {findMacros = true; continue;}

                if (findMacros == false) {continue;}

                if (line.find("class") != std::string::npos || line.find("struct") != std::string::npos) {
                    if (std::regex_search(line, match, classPattern)) {
                        std::string className = match[1].str();

                        std::list<std::string> baseClasses = ExtractBaseClasses(line);
                        GenerateSerializeMacros(className, baseClasses, cfg);
                        findMacros = false;
                    }
                }
            }
        }
    }

    void MacrosGenerator::GenerateConfig(std::vector<File> &files) {
        ACLASS(files);

        for (auto &file : files) {
            file.PushBuffer();
        }
    }
}