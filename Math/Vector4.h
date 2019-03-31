#pragma once
#include <cmath>
#include "Matrix4x4.h"
struct Vector4
{
public: 
	float x;
	float y;
	float z;
	float w;

public: 
	
	Vector4():x(0),y(0),z(0),w(1) {}
	Vector4(float x, float y, float z,float w) : x(x), y(y), z(z),w(w) {}
	Vector4(float x,float y,float z) : x(x),y(y),z(z),w(1){}
	Vector4(const Vector4& a) : x(a.x), y(a.y), z(a.z),w(a.w) {}
	Vector4& operator=(const Vector4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}
	bool operator ==(const Vector4& a) const
	{
		return (x == a.x) && (y == a.y) && (z == a.z) && (w == a.w);
	}
	bool operator !=(const Vector4& other) const
	{
		return (x != other.x) || (y != other.y) || (z != other.z) || (w != other.w);
	}
	Vector4 operator ~() const
	{
		return Vector4(-x, -y, -z, w);
	}
	Vector4 operator +(const Vector4& other) const
	{
		return Vector4(x + other.x, y + other.y, z + other.z,w);
	}
	Vector4 operator -(const Vector4& other) const
	{
		return Vector4(x - other.x, y - other.y, z - other.z,w);
	}
	Vector4 operator *(float a) const
	{
		return Vector4(x * a, y * a, z * a,w);
	}

	Vector4 operator /(float a) const
	{
		return Vector4(x / a, y / a, z / a,w);
	}
	float operator *(const Vector4& other) const  
	{
		return x * other.x + y * other.y + z * other.z;
	}
	Vector4 operator *(const Matrix4x4& m) const 
	{
		return Vector4
			(x * m.m00 + y * m.m10 + z * m.m20 + w * m.m30,
			x * m.m01 + y * m.m11 + z * m.m21 + w * m.m31,
			x * m.m02 + y * m.m12 + z * m.m22 + w * m.m32,
			w * m.m03 + y * m.m13 + z * m.m23 + w * m.m33);
	}
	
	float Magnitude()
	{
		return sqrt(x * x + y * y + z * z);
	}


public:
  inline static Vector4 Normalize(const Vector4& vec4)
  {
    float magSq = vec4.x * vec4.x + vec4.y * vec4.y + vec4.z * vec4.z;
    Vector4 vecNor;
    if (magSq > 0.0f)
    {
      float oneOverMag = 1.0f / sqrt(magSq);
      vecNor.x = vec4.x * oneOverMag;
      vecNor.y = vec4.y *oneOverMag;
      vecNor.z = vec4.z * oneOverMag;
    }
    return vecNor;
  }
	inline static Vector4 CrossProduct(const Vector4& a, const Vector4& b) 
	{
		return Vector4(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x,
			0
			);
	}

	inline static float DotProduct(const Vector4& a, const Vector4& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline static float Distance(const Vector4& a, const Vector4& b)
	{
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		float dz = a.z - b.z;
		return sqrt(dx * dx + dy * dy + dz * dz);
	}
};


