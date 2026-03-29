#pragma once
#include <string>

class MyComponent {
    friend class MyModule;
    friend class MyModuleData;

    private:
        std::string _word = "Hello Module";

    private:
        MyComponent() = default;

    public:
        ~MyComponent() = default;
};
