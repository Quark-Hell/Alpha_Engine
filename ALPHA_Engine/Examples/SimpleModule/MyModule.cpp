//System exist for work with data
//No need to store data here
//Otherwise data will be private and also this system can work with it

//In constructor, you should pass 2 arguments
//1 - vector of tokens data that you need in system
//My engine find it and invoke function EntryPoint() with needed data
//Engine not guaranteed that you data be founded
//Check it like this - if (data[0] == nullptr)
//But Engine guaranteed data type
//So you can use reinterpret_cast or static_cast

//2 - order your system
//All system will be invoked one by one
//From system with minimal order to system with maximum order

//Order cannot be identical
//Otherwise Engine aborted

#include "MyModule.h"
#include "MyModuleData.h"

#include <iostream>

MyModule::MyModule() : System({"MyModuleData"}, 500) {}

void MyModule::EntryPoint(std::vector<Core::SystemData*>& data) {
    if (data[0] == nullptr)
        return;

    auto* buffer = reinterpret_cast<MyModuleData*>(data[0]);
    for (size_t i = 0; i < buffer->GetAllData().size(); i++) {
        std::cout << buffer->GetData(i)._word << " by position: " << i << std::endl;
    }
}