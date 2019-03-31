#pragma once
struct EulerAngles
{
	float x, y, z;
	EulerAngles(float x, float y, float z)
		:x(x),y(y),z(z)
	{

	}

	EulerAngles() = default;

	EulerAngles(const EulerAngles& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	EulerAngles& operator += (const EulerAngles& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
};