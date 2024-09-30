#pragma once

#include "BaseConfig.h"

namespace Register {
	enum ALPHA_ENGINE_API UserScriptType : unsigned short {
		Actor = 0,
		Component = 1
	};

	class ALPHA_ENGINE_API UserScript
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
