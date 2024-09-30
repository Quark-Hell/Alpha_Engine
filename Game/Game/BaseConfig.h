#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>  
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <queue>
#include <algorithm>
#include <thread>
#include <ctime>
#include <set>
#include <array>
#include <optional>
#include <cstring> 
#include <type_traits>
#include <map>

#ifdef ALPHA_Engine
#define ALPHA_ENGINE_API __declspec(dllexport)
#else
#define ALPHA_ENGINE_API __declspec(dllimport)
#endif