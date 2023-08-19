#pragma once
#include "Basical_Type.h"
#include "Modules/Module.h"
#include "Modules/Transform.h"

class MovableModule : public Module, public Transform
{
public:
	MovableModule();
	virtual ~MovableModule();

private:

};


