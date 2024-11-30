#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

#include "File.h"
#include "SystemRegistrator.h"

namespace Utility {
    class Configurator {
    private:
        std::vector<File> _configFiles;
        std::vector<File> _headers;
        std::vector<File> _source;

        std::vector<File> _configGenerated;
        std::vector<File> _headersGenerated;
        std::vector<File> _sourceGenerated;

        SystemRegistrator _registrator;

        const std::unordered_map<std::string, std::vector<File>&> _filesType = {
            {".h", _headers},
            {".hpp", _headers},
            {".c", _source},
            {".cpp", _source},
            {".cfg", _configFiles}
        };

        const std::unordered_map<std::string, std::string> _config = {
            {"ACLASS()",""},
            {"GENERATE_BODY()",""},
        };

    private:
        void GenerateClassHierarchy(const std::filesystem::directory_entry& file);
        void GenerateConfig(const std::filesystem::directory_entry& file);

    public:
        Configurator();

        void IncludeFiles(const std::filesystem::path& directory);
        void LoadFilesContent();


        void WriteToFile();
    };
}

#endif //CONFIGURATOR_H
