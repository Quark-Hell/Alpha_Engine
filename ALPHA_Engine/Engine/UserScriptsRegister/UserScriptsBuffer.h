#pragma once

#include "UserScript.h"
#include "Core/ECS/TSystemData.h"

namespace Register {
    class UserScriptsBuffer final : public Core::TSystemData<UserScript> {
    private:
        UserScriptsBuffer();

    public:
        static UserScriptsBuffer *GetInstance();

        static UserScript *CreateUserScript(UserScript *script);

        ~UserScriptsBuffer() override = default;
    };

    inline UserScriptsBuffer* buffer = UserScriptsBuffer::GetInstance();
}
