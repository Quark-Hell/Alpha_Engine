#include "Configurator.h"

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
                auto it = _filesType.find(entry.path().extension());
                if (it != _filesType.end()) {
                    it->second.emplace_back(entry.path().filename(), entry.path(), entry.path().extension());
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
    }

}

int main() {

    Utility::Configurator config;
    //config.IncludeFiles(USER_FILES_DIRECTORY);
    config.IncludeFiles(CONFIG_SOURCE);
    config.LoadFilesContent();
    config.WriteToFile();

    return 0;
}