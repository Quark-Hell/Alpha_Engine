#include "Configurator.h"

#include <unordered_map>
#include <filesystem>
#include <iostream>

namespace Utility {
    Configurator::Configurator() {
        for (auto& it : _filesType) {
            it.second.reserve(16);
        }
    }

    void Configurator::IncludeFiles(const std::filesystem::path& directory) {
        std::cout << "Path to directory: " << directory << std::endl;

        for(const auto& entry : std::filesystem::directory_iterator(directory)) {
            if(entry.is_directory()) {IncludeFiles(entry.path());}

            if(entry.is_regular_file()) {
                //Add file to container
                auto it = _filesType.find(entry.path().extension().string());
                if (it != _filesType.end()) {
                    const std::filesystem::path& filePath = entry.path();
                    std::string fileName = filePath.filename().string();
                    if (fileName.find(".generated") != std::string::npos) {continue;}

                    it->second.emplace_back(filePath.stem() , filePath.parent_path() , filePath.extension());
                }
            }
        }
    }

    void Configurator::LoadFilesContent() {
        for (auto& it : _filesType) {
            for (auto& file : it.second) {
                file.LoadBuffer();
            }
        }
    }

    void Configurator::WriteToFile() {
        _registrator.GenerateConfig(_configFiles);
        _macrosGenerator.GenerateConfig(_headers);
    }

}

int main() {
    Utility::Configurator config;

    std::string sourceDir;
    std::string configDir;

    while (true) {
        std::cout << "Enter path to sources directory or enter \"null\" for skip it" << std::endl;
        std::getline(std::cin, sourceDir);

        if (sourceDir == "null") {break;}

        if (!(std::filesystem::exists(sourceDir) && std::filesystem::is_directory(sourceDir))) {
            std::cout << "Directory does not exist: " << sourceDir << std::endl;
        }
        else {
            config.IncludeFiles(sourceDir);
            break;
        }
    }
    while (true) {
        std::cout << "Enter path to configs directory or enter \"null\" for skip it" << std::endl;
        std::getline(std::cin, configDir);

        if (configDir == "null") {break;}

        if (!(std::filesystem::exists(configDir) && std::filesystem::is_directory(configDir))) {
            std::cout << "Directory does not exist: " << configDir << std::endl;
        }
        else {
            config.IncludeFiles(configDir);
            break;
        }
    }

    config.LoadFilesContent();
    config.WriteToFile();

    return 0;
}