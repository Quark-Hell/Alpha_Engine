#pragma once

#include <bitsery/bitsery.h>
#include <bitsery/adapter/buffer.h>

#include <bitsery/brief_syntax.h>
#include <bitsery/brief_syntax/array.h>
#include <bitsery/brief_syntax/bitset.h>
#include <bitsery/brief_syntax/chrono.h>
#include <bitsery/brief_syntax/deque.h>
#include <bitsery/brief_syntax/forward_list.h>
#include <bitsery/brief_syntax/list.h>
#include <bitsery/brief_syntax/map.h>
#include <bitsery/brief_syntax/memory.h>
#include <bitsery/brief_syntax/optional.h>
#include <bitsery/brief_syntax/queue.h>
#include <bitsery/brief_syntax/set.h>
#include <bitsery/brief_syntax/stack.h>
#include <bitsery/brief_syntax/string.h>
#include <bitsery/brief_syntax/tuple.h>
#include <bitsery/brief_syntax/unordered_map.h>
#include <bitsery/brief_syntax/unordered_set.h>
#include <bitsery/brief_syntax/variant.h>
#include <bitsery/brief_syntax/vector.h>

#include <bitsery/ext/inheritance.h>

#include <bitsery/adapter/stream.h>

#include "Core/Logger/Logger.h"

#define SERIALIZE(...)                                                                                              \
friend bitsery::Access;                                                                                             \
template<typename S>		                                                                                        \
void serialize(S& s) {                                                                                              \
    s(__VA_ARGS__);				                                                                                    \
}




#define VIRTUAL_SERIALIZE(type, ...)                                                                                \
friend bitsery::Access;                                                                                             \
template<typename S>		                                                                                        \
void serialize(S& s) {                                                                                              \
        s.ext(*this, bitsery::ext::BaseClass<type>{});                                                              \
        std::cout << "type" << std::endl;                                                                           \
        s(__VA_ARGS__);				                                                                                \
}


namespace Core {
    class Serialized {
    protected:
        using Buffer = std::vector<uint8_t>;

    protected:
        Buffer _buffer;
        size_t _size = 0;

    public:
        Serialized() = default;
        virtual ~Serialized() = default;
    };
}


