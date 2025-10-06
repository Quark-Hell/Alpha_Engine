//This class exist only for user API
//Do not use some function from this in Engine

#pragma once

namespace Core {
    class GameObject;
    class FakeObject;
    class Component;

    class Factory {
    private:
        Factory() = default;
        ~Factory() = default;

    public:
        static bool RemoveObject(const Core::GameObject *object);

        static Core::GameObject& CreateObject();
        static Core::FakeObject& CreateFakeObject();
    };
}
