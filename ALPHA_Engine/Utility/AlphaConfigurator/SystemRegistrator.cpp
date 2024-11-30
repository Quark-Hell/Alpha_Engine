#include "SystemRegistrator.h"

#include <fstream>
#include <iostream>

namespace Utility {
    void SystemRegistrator::Include(std::vector<File>& files, File& output) {
        bool found = false;
        output._generatedBuffer.emplace_back("//================INCLUDE================//");

        for (const auto& cfg : files) {
            for (auto& line : cfg._sourceBuffer) {
                if (_config.find(line) != _config.end()) {
                    if (line == "[INCLUDE]") {
                        found = true;
                        continue;
                    }
                    found = false;
                    continue;
                }

                if (found) {
                    output._generatedBuffer.push_back(line);
                }
            }
        }
        output._generatedBuffer.emplace_back("//================INCLUDE================//");
        output._generatedBuffer.emplace_back("");
    }
    void SystemRegistrator::Variables(std::vector<File>& files, File& output) {
        bool found = false;
        output._generatedBuffer.emplace_back("//================VARIABLE================//");

        for (const auto& cfg : files) {
            for (auto& line : cfg._sourceBuffer) {
                if (_config.find(line) != _config.end()) {
                    if (line == "[VARIABLE]") {
                        found = true;
                        continue;
                    }
                    found = false;
                    continue;
                }

                if (found) {
                    output._generatedBuffer.push_back(line);
                }
            }
        }

        output._generatedBuffer.emplace_back("//================VARIABLE================//");
        output._generatedBuffer.emplace_back("");
    }
    void SystemRegistrator::Modules(std::vector<File>& files, File& output) {
        output._generatedBuffer.emplace_back("//================MODULE================//");

        output._generatedBuffer.emplace_back("namespace Core {");
        output._generatedBuffer.emplace_back("\t//This function will be invoked before general cycle");
        output._generatedBuffer.emplace_back("\t//Use this for initialize global data");
        output._generatedBuffer.emplace_back("\tvoid InstanceModule() {");

        bool found = false;

        for (const auto& cfg : files) {
            for (auto& line : cfg._sourceBuffer) {
                if (_config.find(line) != _config.end()) {
                    if (line == "[MODULE]") {
                        found = true;
                        continue;
                    }
                    found = false;
                    continue;
                }

                if (found) {
                    output._generatedBuffer.push_back("\t\t" + line);
                }
            }
        }

        output._generatedBuffer.emplace_back("\t}");
        output._generatedBuffer.emplace_back("}");
        output._generatedBuffer.emplace_back("//================MODULE================//");
    }

    void SystemRegistrator::GenerateConfig(std::vector<File>& files) {
        const std::string outputPath = CONFIG_OUTPUT;
        const std::string filename = "Modules";
        const std::string extension = ".h";

        File output{filename, outputPath, extension};

        Include(files, output);
        Variables(files, output);
        Modules(files, output);

        files.push_back(std::move(output));
        output.PushBuffer();
    }

}
