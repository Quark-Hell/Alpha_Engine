#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <filesystem>
#include <string>
#include <unordered_map>

class Configurator {
private:
    const std::string _fileTemplate = "Module.cfg";

    std::unordered_map<std::string, std::string> _config;

    const std::string _includeToken  = "[INCLUDE]";
    const std::string _variableToken = "[VARIABLE]";
    const std::string _moduleToken   = "[MODULE]";

private:
    void GenerateConfig(const std::filesystem::directory_entry& file);

public:
    Configurator();

    void ReadFromFile(const std::filesystem::path& directory);
    void WriteToFile(const std::string& directory);
};

#endif //CONFIGURATOR_H
