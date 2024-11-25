//In constructor, you should invoke base constructor
//And pass name for you data
//Systems can find your data only by token
//Many system(module) data cannot have same token
//Token should be unique
//Otherwise Engine just aborted with critical error

//All that you need in system data it's function for creating your data
//Another function like delete data or find data already exist in TSystemData

#include "MyModuleData.h"

MyModuleData::MyModuleData(): TSystemData("MyModuleData") {}

MyComponent* MyModuleData::CreateComponent() {
    _data.emplace_back(std::unique_ptr<MyComponent>(new MyComponent()));
    return _data.back().get();
}
