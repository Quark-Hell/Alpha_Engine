#pragma once

#include "BaseConfig.h"

namespace Register {
	class _declspec(dllexport) UserScript
	{
	public:
		UserScript();
		virtual ~UserScript();

		void Start();
		void Update();
		void End();

	private:

	};
}
