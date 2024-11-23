#pragma once

#include "UserScript.h"
#include "Core/ECS/TSystemData.h"

namespace Register {
    class UserScriptsBuffer final : public Core::TSystemData<UserScript> {
    public:
        UserScriptsBuffer();
        UserScript *CreateUserScript(UserScript *script);

        ~UserScriptsBuffer() override = default;
    };
}
