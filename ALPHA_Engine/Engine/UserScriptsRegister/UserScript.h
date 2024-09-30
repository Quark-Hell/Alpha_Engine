#pragma once

#include "BaseConfig.h"
#include "Core/Modules/Module.h"

namespace Register {
	enum UserScriptType : unsigned short {
		Actor = 0,
		Component = 1
	};

	class UserScript
	{
	public:
		UserScript(enum Register::UserScriptType type);
		virtual ~UserScript();

		void virtual Start();
		void virtual Update();
		void virtual End();

	private:

	};
}
