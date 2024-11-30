#pragma once
#include <utility>

#include "UserScriptsRegister/UserScriptConfig.h"

namespace WindowsManager {
	class Window;
}

#define ACLASS()
#define GENERATE_BODY()

ACLASS()
class MyScript final : public Register::UserScript {
	GENERATE_BODY()

	private:
	Core::Object* Player = nullptr;
	float moveSensitive = 10;

	WindowsManager::Window* win1 = nullptr;
	WindowsManager::Window* win2 = nullptr;

	WindowsManager::Window* win3 = nullptr;
	WindowsManager::Window* win4 = nullptr;

	public:
	MyScript() = default;

	void Start() override;
	void Update() override;
	void End() override;

	void Print();

    void CameraRotate();

	void LeftMoveCamera();
	void RightMoveCamera();
	void ForwardMoveCamera();
	void BackwardMoveCamera();
    void UpMoveCamera();
    void DownMoveCamera();

	void ShowCursor();
	void HideCursor();

	void GenerateCubeMap();
	void GenerateLightSource();
	void GenerateEarth();
	void GenerateSun();
};

#include "Core/Serialization/TSerialized.h"

class MyStruct : public Core::TSerialized<MyStruct>
{
public:
	MyStruct() = default;
	MyStruct(const uint32_t n, std::string nam, const std::vector<float>& vec) : i(n), name(std::move(nam)), fs(vec) {}
	~MyStruct() override = default;

public:
	uint32_t i{};
	std::string name;
	std::vector<float> fs;

	//SERIALIZE(i, name ,fs)

	template<typename S>
	void serialize(S& s) {
		s(i, name, fs);
	}
};

class MyStruct2 : public MyStruct {
public:
	float dickSize;
	MyStruct2() = default;
	MyStruct2(const float size, const uint32_t n, std::string nam, const std::vector<float>& vec) {
		dickSize = size;
		name = std::move(nam);
		fs = vec;
		i = n;
	}

	~MyStruct2() override = default;

	template<typename S>
	void serialize(S& s)
	{
		s.ext(*this, bitsery::ext::BaseClass<MyStruct>{});
		s.value4b(dickSize);
		std::cout << "test" << std::endl;
	}

	//VIRTUAL_SERIALIZE(MyStruct,dickSize)
};

template <typename T>
void printType()
{
#ifndef _MSC_VER
	std::cout << __PRETTY_FUNCTION__ << '\n';
#else
	std::cout << __FUNCSIG__ << '\n';
#endif
};