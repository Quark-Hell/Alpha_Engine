#pragma once

#include "Core/Components/Component.h"

namespace Register {
    class UserScript : public Core::Component {
        friend class Registry;
        friend class UserScriptsBuffer;

    private:
        bool _isStarted = false;

    protected:
        UserScript();

    public:
        ~UserScript() override;

        //void Delete() final;

        void virtual Start();
        void virtual Update();
        void virtual End();
    };
}
