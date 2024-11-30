#ifndef SYSTEMREGISTRATOR_H
#define SYSTEMREGISTRATOR_H

#include <set>
#include "File.h"

namespace Utility {
    class SystemRegistrator {
        private:
        const std::set<std::string> _config = {
            {"[INCLUDE]"},
            {"[VARIABLE]"},
            {"[MODULE]"}
        };

        private:
          void Include(std::vector<File>& files, File& output);
          void Variables(std::vector<File>& files, File& output);
          void Modules(std::vector<File>& files, File& output);

        public:
          SystemRegistrator() = default;
          ~SystemRegistrator() = default;

          void GenerateConfig(std::vector<File>& files);
    };
}

#endif //SYSTEMREGISTRATOR_H
