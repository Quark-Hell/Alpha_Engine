#pragma once
#include "Basical_Type.h"

class Module;

enum SubModulesList {
	SubModuleType = 0,
	MaterialType = 1,
};

class SubModule {


public:
	std::string Name = "Undefined";

protected:
	Module* ParentModule = nullptr;

public:
	SubModule();
	~SubModule();

	virtual SubModulesList GetType() = 0;

	virtual Module* GetParentModule();
	virtual void SetParentModule(const Module& parent);
};