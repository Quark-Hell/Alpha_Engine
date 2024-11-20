#pragma once

#include "UserScript.h"
#include "Core/ECS/TSystemData.h"

namespace Register {
    class UserScriptsBuffer final : public Core::TSystemData<UserScript> {

        private:
            UserScriptsBuffer();

        public:
            static UserScriptsBuffer* GetInstance();

            static UserScript* CreateUserScript(UserScript* script);

            UserScript& GetData(size_t pos) override;
            const std::vector<std::unique_ptr<UserScript>>& GetAllData() override;

            bool DestroyData(size_t pos) override;
            bool DestroyData(UserScript* ptr) override;

            ~UserScriptsBuffer() override = default;
    };
}