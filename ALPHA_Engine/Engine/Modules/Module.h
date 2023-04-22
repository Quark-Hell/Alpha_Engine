#pragma once
#include "Basical_Type.h"

class Object;

class Module
{
private:
	std::string _name;
	Object* ParentObject = nullptr;

private:
	friend class Render;
	friend class Collision;
	friend class Object;

public:
	void Rename(std::string name);
	std::string GetName();
	Object* GetParentObject();

private:
	virtual void Test();
};
