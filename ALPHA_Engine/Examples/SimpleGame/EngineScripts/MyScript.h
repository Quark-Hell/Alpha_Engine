#pragma once
#include "UserScriptsRegister/UserScriptConfig.h"
#include "Core/Serialization/TSerialized.h"
#include "MyScript.generated.h"

#include "AnomalyEngine/Components/Mesh.h"

ACLASS()
class Data {
	public:
	    float f1 = 100;
	    float f2 = 200;
	    float f3 = 300;

		Data() = default;
		Data(const float f1, const float f2, const float f3) : f1(f1), f2(f2), f3(f3) {}
		virtual ~Data() = default;

		SERIALIZE_DATA(f1,f2,f3);
};

ACLASS()
class DerivedData final : public virtual  Data {
	public:
		float f4 = 400;

	    DerivedData() = default;
		DerivedData(const float v1, const float v2, const float v3, const float v4) : Data(v1, v2, v3) , f4(v4) {}
		~DerivedData() override = default;

		SERIALIZE_DERIVEDDATA(f4);
};


class MyScript final : public Register::UserScript {
private:
	AnomalyEngine::Mesh* cubeMesh;

public:
	MyScript() = default;

	void Start() override;
	void Update() override;
	void End() override;

	void Serialization();
};
