#include "UserScriptsBuffer.h"

#include <Core/Factory.h>
#include <Core/Object.h>

namespace Register {
    UserScriptsBuffer::UserScriptsBuffer() : Core::TSystemData<UserScript>("UserScriptsBuffer") {
        _data.reserve(64);
    }
}
