//Module and Module data should be registration in world
//For this I leave global Core::InstanceModule() function
//Initialize all your classes in this function

#include "Core/World.h"
#include "MyModule.h"
#include "MyModuleData.h"

MyModule* myModule;
MyModuleData* myModuleData;

namespace Core {
    void InstanceModule() {
        myModule = new MyModule();
        myModuleData = new MyModuleData();

        myModuleData->CreateComponent();
        myModuleData->CreateComponent();
    }
}