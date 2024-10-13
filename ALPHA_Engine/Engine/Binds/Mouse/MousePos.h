#pragma once

#include "Core/Math/Vectors.h"

namespace BindsEngine {

class MousePos {
public:
	Core::Vector2 Position;

public:
	void SetMousePos(MousePos MousePos);
	MousePos GetMousePos();
	explicit MousePos(float XPos = 0, float YPos = 0);

#pragma region Operators overload
	//-----------------------------------------------------------//
	void operator=(const MousePos value);
	void operator=(const MousePos* value);

	void operator=(const float value);
	void operator=(const float* value);
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos operator+(const MousePos value);
	MousePos operator+(const MousePos* value);

	MousePos operator+(const float value);
	MousePos operator+(const float* value);
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos operator-(const MousePos value);
	MousePos operator-(const MousePos* value);

	MousePos operator-(const float value);
	MousePos operator-(const float* value);
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos operator*(const MousePos value);
	MousePos operator*(const MousePos* value);

	MousePos operator*(const float value);
	MousePos operator*(const float* value);
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos operator/(const MousePos value);
	MousePos operator/(const MousePos* value);

	MousePos operator/(const float value);
	MousePos operator/(const float* value);
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator+=(const MousePos value);
	void operator+=(const MousePos* value);

	void operator+=(const float value);
	void operator+=(const float* value);
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator-=(const MousePos value);
	void operator-=(const MousePos* value);

	void operator-=(const float value);
	void operator-=(const float* value);
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator*=(const MousePos value);
	void operator*=(const MousePos* value);

	void operator*=(const float value);
	void operator*=(const float* value);
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void operator/=(const MousePos value);
	void operator/=(const MousePos* value);

	void operator/=(const float value);
	void operator/=(const float* value);
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool operator!=(const MousePos value) const;
	bool operator!=(const MousePos* value) const;

	bool operator!=(const float value) const;
	bool operator!=(const float* value) const;
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool operator==(const MousePos value) const;
	bool operator==(const MousePos* value) const;

	bool operator==(const float value) const;
	bool operator==(const float* value) const;
	//-----------------------------------------------------------//
#pragma endregion
};

} // BindsEngine
