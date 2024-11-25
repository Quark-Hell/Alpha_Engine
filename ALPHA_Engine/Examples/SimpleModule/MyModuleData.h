#pragma once

#include "MyComponent.h"
#include "Core/ECS/TSystemData.h"

class MyModuleData  final : public Core::TSystemData<MyComponent> {
    friend class MyModule;

public:
    MyModuleData();
    ~MyModuleData() override = default;

    MyComponent* CreateComponent();
};
