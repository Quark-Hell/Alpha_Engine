#pragma once

#include "BaseConfig.h"
#include "Core/Components/Component.h"

namespace Register {
	class UserScript : public Core::Component
	{
	friend class Registry;

	private:
		bool _isStarted = false;

	public:
		UserScript();
		~UserScript() override;

		//void Delete() final;

		void virtual Start();
		void virtual Update();
		void virtual End();
	};
}
