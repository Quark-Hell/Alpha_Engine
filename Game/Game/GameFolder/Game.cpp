
#include "Game.h"
#include <iostream>

MyScript* script = new MyScript(Register::UserScriptType::Component);

//Call by constructor
void MyScript::Start() {

}
//Call every frame
void MyScript::Update() {
	std::cout << "Updated" << std::endl;
}
//Call by destructor
void MyScript::End() {

}

