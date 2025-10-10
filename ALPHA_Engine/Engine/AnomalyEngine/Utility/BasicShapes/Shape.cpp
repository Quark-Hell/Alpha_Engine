#include "Shape.h"

namespace AnomalyEngine {
	Shape::Shape(Color shapeColor) :
		ShapeColor(shapeColor) { }

	bool Shape::Create() {
		return true;
	}
}