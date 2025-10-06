#include "UserScriptsBuffer.h"

namespace Register {
    UserScriptsBuffer::UserScriptsBuffer(size_t initialBufferSize) : Core::TSystemData<UserScript>("UserScriptsBuffer", initialBufferSize) {}
}
