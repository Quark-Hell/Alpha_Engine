#include "Configurator.h"
#include <iostream>
#include <fstream>

Configurator::Configurator() {
    _config["[INCLUDE]"]  = "";
    _config["[VARIABLE]"] = "";
    _config["[MODULE]"]   = "";
}

void Configurator::WriteToFile(const std::string& directory) {
    if (!std::filesystem::exists(directory)) {
        std::filesystem::create_directory(directory);
    }

    const std::string filePath = directory + "/" + "Config.h";
    std::ofstream outputFile(filePath, std::ios::out | std::ios::trunc);

    if (!outputFile) {
        std::cerr << "Failed to create file: " << filePath << '\n';
        return;
    }

    auto section = _config.find("[INCLUDE]");
    outputFile << section->second << std::endl;

    section = _config.find("[VARIABLE]");
    outputFile << section->second << std::endl;

    outputFile <<
        "namespace Core {\n"
        "    //This function will be invoked before general cycle\n"
        "    //Use this for initialize global data\n"
        "    void InstanceModule() {\n";

    section = _config.find("[MODULE]");
    outputFile << section->second;

    outputFile <<
    "    }\n"
    "}";

    outputFile.close();
}

void Configurator::GenerateConfig(const std::filesystem::directory_entry& file) {
    std::ifstream inputFile(file.path());
    if (!inputFile.is_open()) {
        std::cerr << "filed to open file: " << file.path() << std::endl;
        return;
    }

    //Read first line
    std::string line;
    std::getline(inputFile, line);
    auto place = _config.find(line);

    while (std::getline(inputFile, line)) {
        auto check = _config.find(line);
        if (check != _config.end()) {
            place = check;
            continue;
        }
        if (place->first == "[MODULE]") {
            place->second += "\t\t" + line + "\n";
            continue;
        }
        place->second += line + "\n";
    }
    const auto last = _config.find("[MODULE]");
    last->second += "\n";
    inputFile.close();
}

void Configurator::ReadFromFile(const std::filesystem::path& directory) {
    for(const auto& entry : std::filesystem::directory_iterator(directory)) {
        if(entry.is_directory()) {
            ReadFromFile(entry.path());
        }
        else if(entry.is_regular_file()) {
            if(entry.path().filename() == _fileTemplate) {
                GenerateConfig(entry);
                std::cout << std::endl;
            }
        }
    }
}

int main() {
    Configurator config;
    config.ReadFromFile("Configs");
    config.WriteToFile("headers");

    return 0;
}