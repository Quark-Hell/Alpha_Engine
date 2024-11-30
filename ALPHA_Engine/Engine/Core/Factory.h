//This class exist only for user API
//Do not use some function from this in Engine

#pragma once

namespace Core {
    class Object;
    class Component;

    class Factory {
    private:
        Factory() = default;
        ~Factory() = default;

    public:
        static bool RemoveObject(const Core::Object *object);
        static Core::Object& CreateObject();
    };
}
