#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

#include "File.h"
#include "SystemRegistrator.h"
#include "MacrosGenerator.h"

namespace Utility {
    class Configurator {
    private:
        std::vector<File> _configFiles;
        std::vector<File> _headers;
        std::vector<File> _source;

        SystemRegistrator _registrator;
        MacrosGenerator _macrosGenerator;

        const std::unordered_map<std::string, std::vector<File>&> _filesType = {
            {".h", _headers},
            {".hpp", _headers},
            {".c", _source},
            {".cpp", _source},
            {".cfg", _configFiles}
        };

    public:
        Configurator();

        void IncludeFiles(const std::filesystem::path& directory);
        void LoadFilesContent();


        void WriteToFile();
    };
}

#endif //CONFIGURATOR_H
