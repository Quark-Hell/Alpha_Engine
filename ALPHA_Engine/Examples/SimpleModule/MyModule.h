#pragma once

#include "Core/ECS/System.h"

class MyModule final : public Core::System  {
private:
    void EntryPoint(std::vector<Core::SystemData*>& data) override;

public:
    MyModule();
    ~MyModule() override = default;
};