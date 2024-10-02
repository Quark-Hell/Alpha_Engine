#pragma once
#include "BaseConfig.h"
#include "EngineDefines.h"


namespace Core {
	class Geometry;	
}

namespace Register {
	class UserScript;
}

namespace Core::Creator {
	class Creator {
		class Core::Geometry;

		template<typename T,
			std::is_same<T, Core::Geometry>,
			std::is_same<T, Register::UserScript>
		>
		std::shared_ptr<T> static CreateComponent() {
			return std::shared_ptr<T>();
		}
	};
}