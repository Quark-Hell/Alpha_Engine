//
// Created by admin on 11.10.24.
//

#include "MousePos.h"

namespace BindsEngine {
    void MousePos::SetMousePos(MousePos MousePos) {
        MousePos::XPos = MousePos.XPos;
        MousePos::YPos = MousePos.YPos;
    }
    MousePos MousePos::GetMousePos() {
        return(MousePos{XPos,YPos});
    }

    MousePos::MousePos(float XPos = 0, float YPos = 0) {
        MousePos::XPos = XPos;
        MousePos::YPos = YPos;
    }

    #pragma region Operators overload
	//-----------------------------------------------------------//
	void MousePos::operator=(const MousePos value) {
		Position = value.Position;
	}
	void MousePos::operator=(const MousePos* value) {
		Position = value->Position;
	}

	void MousePos::operator=(const float value) {
		Position.X = value;
		Position.Y = value;
	}
	void MousePos::operator=(const float* value) {
		Position.X = *value;
		Position.Y = *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos MousePos::operator+(const MousePos value) {
		return MousePos(Position.X + value.Position.X, Position.Y + value.Position.Y);
	}
	MousePos MousePos::operator+(const MousePos* value) {
		return MousePos(Position.X + value->Position.X, Position.Y + value->Position.Y);
	}

	MousePos MousePos::operator+(const float value) {
		return MousePos(Position.X + value, Position.Y + value);
	}
	MousePos MousePos::operator+(const float* value) {
		return MousePos(Position.X + *value, Position.Y + *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos MousePos::operator-(const MousePos value) {
		return MousePos(Position.X - value.Position.X, Position.Y - value.Position.Y);
	}
	MousePos MousePos::operator-(const MousePos* value) {
		return MousePos(Position.X - value->Position.X, Position.Y - value->Position.Y);
	}

	MousePos MousePos::operator-(const float value) {
		return MousePos(Position.X - value, Position.Y - value);
	}
	MousePos MousePos::operator-(const float* value) {
		return MousePos(Position.X - *value, Position.Y - *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos MousePos::operator*(const MousePos value) {
		return MousePos(Position.X * value.Position.X, Position.Y * value.Position.Y);
	}
	MousePos MousePos::operator*(const MousePos* value) {
		return MousePos(Position.X * value->Position.X, Position.Y * value->Position.Y);
	}

	MousePos MousePos::operator*(const float value) {
		return MousePos(Position.X * value, Position.Y * value);
	}
	MousePos MousePos::operator*(const float* value) {
		return MousePos(Position.X * *value, Position.Y * *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	MousePos MousePos::operator/(const MousePos value) {
		return MousePos(Position.X / value.Position.X, Position.Y / value.Position.Y);
	}
	MousePos MousePos::operator/(const MousePos* value) {
		return MousePos(Position.X / value->Position.X, Position.Y / value->Position.Y);
	}

	MousePos MousePos::operator/(const float value) {
		return MousePos(Position.X / value, Position.Y / value);
	}
	MousePos MousePos::operator/(const float* value) {
		return MousePos(Position.X / *value, Position.Y / *value);
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void MousePos::operator+=(const MousePos value) {
		Position += value.Position;
	}
	void MousePos::operator+=(const MousePos* value) {
		Position += value->Position;
	}

	void MousePos::operator+=(const float value) {
		Position += value;
	}
	void MousePos::operator+=(const float* value) {
		Position += *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void MousePos::operator-=(const MousePos value) {
		Position -= value.Position;
	}
	void MousePos::operator-=(const MousePos* value) {
		Position -= value->Position;
	}

	void MousePos::operator-=(const float value) {
		Position -= value;
	}
	void MousePos::operator-=(const float* value) {
		Position -= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void MousePos::operator*=(const MousePos value) {
		Position *= value.Position;
	}
	void MousePos::operator*=(const MousePos* value) {
		Position *= value->Position;
	}

	void MousePos::operator*=(const float value) {
		Position *= value;
	}
	void MousePos::operator*=(const float* value) {
		Position *= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	void MousePos::operator/=(const MousePos value) {
		Position /= value.Position;
	}
	void MousePos::operator/=(const MousePos* value) {
		Position /= value->Position;
	}

	void MousePos::operator/=(const float value) {
		Position /= value;
	}
	void MousePos::operator/=(const float* value) {
		Position /= *value;
	}
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool MousePos::operator!=(const MousePos value) const {
    	if (Position != value.Position)
    	{
    		return true;
    	}
    	return false;
    }
	bool MousePos::operator!=(const MousePos* value) const {
    	if (Position != value->Position)
    	{
    		return true;
    	}
    	return false;
    }

	bool MousePos::operator!=(const float value) const {
    	if (Position.X != value || Position.Y != value)
    	{
    		return true;
    	}
    	return false;
    }
	bool MousePos::operator!=(const float* value) const {
    	if (Position.X != *value || Position.Y != *value)
    	{
    		return true;
    	}
    	return false;
    }
	//-----------------------------------------------------------//

	//-----------------------------------------------------------//
	bool MousePos::operator==(const MousePos value) const {
    	if (Position == value.Position)
    	{
    		return true;
    	}
    	return false;
    }
	bool MousePos::operator==(const MousePos* value) const {
    	if (Position == value->Position )
    	{
    		return true;
    	}
    	return false;
    }

	bool MousePos::operator==(const float value) const {
    	if (Position == value)
    	{
    		return true;
    	}
    	return false;
    }
	bool MousePos::operator==(const float* value) const {
    	if (Position == *value)
    	{
    		return true;
    	}
    	return false;
    }
	//-----------------------------------------------------------//
#pragma endregion
} // BindsEngine