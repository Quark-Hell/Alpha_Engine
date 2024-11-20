#pragma once

#include <string>

namespace Core {
    class SystemData {
        public:
            const std::string Token;

        protected:
            SystemData(const std::string& token);

        public:
            virtual ~SystemData() = default;
    };
}

