#pragma once
#ifndef BasicalType_H
#define BasicalType_H

#include <iostream>
#include <vector>
#include <string>

struct Vector3
{
public:
	float X;
	float Y;
	float Z;
};

#pragma region Modules

class Module
{
private:
	std::string Name;

public:
	bool Rename(std::string name);

public:
	std::string GetName();

	//TODO:
	Module() {
		Name = "";
	}
};

class Camera : public Module {

};

class Mesh : public Module {
private:
	std::vector <Vector3> Points;
private:
	std::vector <Vector3> Triangles;

public:
	bool CreateMesh(std::vector<Vector3> points, std::vector<Vector3> triangles);

public:
	void DeleteMesh();
};

class Physics : public Module {

};

#pragma endregion

class Object
{
private:
	Vector3 Position;

private:
	std::vector<Module> Modules;

public:
	Vector3 GetPosition();

public:
	void SetPosition(float X, float Y, float Z);

public:
	bool AddModule(class Module some_module);

public:
	bool DeleteModuleByType(class Module some_module);

public:
	bool DeleteModuleByName(std::string name);
};


#endif
