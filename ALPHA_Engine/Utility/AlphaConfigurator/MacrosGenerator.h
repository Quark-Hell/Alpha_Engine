#ifndef MACROSGENERATOR_H
#define MACROSGENERATOR_H

#include <string>
#include <list>
#include <vector>

#include "File.h"

namespace Utility {
    class MacrosGenerator {
    private:
        void ACLASS(std::vector<File> &files);
        void GENERATE_BODY(std::vector<File> &files);

        std::list<std::string> ExtractBaseClasses(const std::string& str);

        void GenerateSerializeMacros(const std::string& className, std::list<std::string>& baseClasses, File& output);

    public:
        MacrosGenerator() = default;
        ~MacrosGenerator() = default;

        void GenerateConfig(std::vector<File> &files);
    };
}


#endif //MACROSGENERATOR_H
