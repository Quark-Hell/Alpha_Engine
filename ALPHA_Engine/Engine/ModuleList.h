#pragma once
#pragma warning(disable : 4250 4244 4305 4267)
#define _USE_MATH_DEFINES

class Module;
class Camera;
class RigidBody;
class Geometry;
class MeshCollider;
class Mesh;
class BoxCollider;
class Light;
class AmbientLight;
class DirectLight;
class PointLight;
class Spotlight;
class SpotLight;
class DebugMesh;

enum ModulesList : unsigned short {
	ModuleType = 0,
	CameraType = 1,
	RigidBodyType = 2,
	GeometryType = 3,
	MeshColliderType = 4,
	MeshType = 5,
	BoxColliderType = 6,
	LightType = 7,
	AmbientLightType = 8,
	DirectLightType = 9,
	PointLightType = 10,
	SpotLightType = 11,
	DebugMeshType = 12,
	UserScriptType = 13
};
