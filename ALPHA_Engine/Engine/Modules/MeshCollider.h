#pragma once
#include "Modules/Geometry.h"
#include "Modules/Collider.h"
#include "Modules/DebugMesh.h"

class MeshCollider : public Collider, public Geometry {
public:
	MeshCollider(std::string linkToFBX);
	MeshCollider();

	~MeshCollider();

	ModulesList GetType();

	bool CreateConvexFromConcave(std::string link);

	bool Create(std::string linkToFBX) override;

#pragma region Redifine from Transfom
	void AddPosition(float X, float Y, float Z) override;
	void AddPosition(Vector3 position) override;

	void SetPosition(float X, float Y, float Z) override;
	void SetPosition(Vector3 position) override;


	void AddRotation(float X, float Y, float Z) override;
	void AddRotation(Vector3 rotation) override;

	void SetRotation(float X, float Y, float Z) override;
	void SetRotation(Vector3 rotation) override;


	void SetScale(float X, float Y, float Z) override;
	void SetScale(Vector3 scale) override;

	void AddOriginPosition(float X, float Y, float Z) override;
	void AddOriginPosition(Vector3 position) override;

	void SetOriginPosition(float X, float Y, float Z) override;
	void SetOriginPosition(Vector3 position) override;

	void ApplyTransformation() override;
#pragma endregion

	void ModuleAdded() override;

#ifdef _DEBUG
protected:
	std::unique_ptr<DebugMesh> _debugMesh = std::make_unique<DebugMesh>();
#endif

private:
	friend class Collision;
	friend class Render;
};