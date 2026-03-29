#pragma once

#include "Shape.h"

namespace AnomalyEngine {
	class Sphere final : public Shape {
	private:
		const size_t _segments = 36;

	public:
		float Radius = 0;

	public:
		Sphere(Color shapeColor = Color::Green);
		~Sphere() override = default;

		bool Create() override;

	};
}