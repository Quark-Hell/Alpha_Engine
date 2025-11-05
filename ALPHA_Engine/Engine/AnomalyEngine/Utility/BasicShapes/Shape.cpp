#include "Shape.h"

#include "Core/Factory.h"

namespace AnomalyEngine {
	Shape::Shape(Color shapeColor) :
		ShapeColor(shapeColor) {

		_geometry = &Core::Factory::CreateResource<Core::Geometry>();
		_binder = std::make_shared<AnomalyEngine::Binder>();
	}

	bool Shape::Create() {
		return true;
	}
}