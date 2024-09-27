#pragma once

#ifdef ALPHA_Engine
	#define ALPHA_ENGINE_API __declspec(dllexport)
#else
	#define ALPHA_ENGINE_API __declspec(dllimport)
#endif

#include <iostream>

#ifdef ALPHA_Engine
int main(int argc, char** argv) {
	std::cout << "Complete";
	return 0;
}
#endif