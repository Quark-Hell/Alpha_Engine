#include "UserScriptsBuffer.h"

namespace Register {
    UserScriptsBuffer::UserScriptsBuffer() : Core::TSystemData<UserScript>("UserScriptsBuffer") {
        _data.reserve(64);
    }
}
