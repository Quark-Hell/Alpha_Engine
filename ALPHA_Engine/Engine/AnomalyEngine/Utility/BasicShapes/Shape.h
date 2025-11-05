#pragma once

#include <vector>

#include "AnomalyEngine/Components/Mesh.h"
#include "AnomalyEngine/Utility/Color.h"

#include "Core/Math/glmMath.h"

namespace AnomalyEngine {
	class Shape;

	template<typename T>
	concept DerivedShape = std::is_base_of_v<Shape, T> && !std::is_same_v<Shape, T>;

	class Shape : public AnomalyEngine::Mesh {
	protected:
		Color ShapeColor = Color::Green;

	protected:
		Shape(Color shapeColor = Color::Green);

	public:
		virtual ~Shape() = default;
		virtual bool Create() = 0;
	};
}