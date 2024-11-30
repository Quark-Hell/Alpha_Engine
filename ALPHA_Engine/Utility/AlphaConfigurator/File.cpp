#include "File.h"

#include <iostream>
#include <fstream>
#include <algorithm>

namespace Utility {
    File::File(std::string name, std::string path, std::string type) :
  sourceName(std::move(name)), sourcePath(std::move(path)), sourceType(std::move(type)) {
        _sourceBuffer.reserve(256); _generatedBuffer.reserve(256);
    }

    void File::PopBuffer(){
        _sourceBuffer.clear();
        _generatedBuffer.clear();
    }

    void File::PushBuffer() {
        std::cout << sourcePath << sourceName << std::endl;

        std::ofstream outputFile(sourcePath + sourceName + ".generated" + sourceType,std::ios::out | std::ios::trunc);
        if (!outputFile.is_open()) {
            std::cout << "filed to open file: " << sourcePath << std::endl;
            return;
        }

        for (auto& it : _generatedBuffer) {
            outputFile << it << std::endl;
        }

        outputFile.close();
    }

    void File::LoadBuffer(){
        PopBuffer();

        std::ifstream inputFile(sourcePath.c_str());
        if (!inputFile.is_open()) {
            std::cout << "filed to open file: " << sourcePath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            if(line.empty()) {continue;}

            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());

            _sourceBuffer.push_back(line);
        }

        inputFile.close();
    }

    const std::string& File::GetSourceName() const { return sourceName; }
    const std::string& File::GetSourcePath() const { return sourcePath; }
    const std::string& File::GetSourceType() const { return sourceType; }
}
