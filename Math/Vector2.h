#pragma once
struct Vector2
{
	float x;
	float y;
	Vector2() {}
	Vector2(float x,float y):x(x),y(y){}

	Vector2 operator *= (const float& factor)
	{
		this->x *= factor;
		this->y *= factor;
		return *this;
	}
};