#include "MyScript.h"

#include "Windows/WindowsSettings.h"

#include "Modules.h"

void MyScript::Serialization() {
    DerivedData data{10,20,30,40};
    DerivedData res{0,0,0,0};

    Core::TSerialized<DerivedData> dataBuffer;
    dataBuffer.Serialize(data);
    dataBuffer.Deserialize(res);

    Core::TSerialized<DerivedData>::SaveData(data,"/Saved.bin");
    Core::TSerialized<DerivedData>::LoadData(data,"/Saved.bin");
}

//Call after created
void MyScript::Start() {
    Serialization();
}
//Call every frame
void MyScript::Update() {

}
//Call before deleted
void MyScript::End() {

}