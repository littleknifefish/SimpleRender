#pragma once
#include <wtypes.h>
#include <cmath>
#include "Matrix4x4.h"
#include "EulerAngles.h"
#include "Vector2.h"
#include "Vertex.h"
#include "Vector4.h"
namespace MathConstant
{
	extern const float PI;
}

struct VertexOut;
class Mathf
{
public:
    	static UINT ColorToUINT(int r, int g, int b)
	{
		//BYTE red = 255 * r/*  color.w*/;
		//BYTE green = 255 * g/* color.w*/;
		//BYTE blue = 255 * b /* color.w*/;
		return (UINT)((BYTE)b | (WORD)((BYTE)g << 8) | (DWORD)((BYTE)r << 16));
	}
	static float Sqrt(float value)
	{
		return sqrt(value);
	}
	static float WarpPI(float theta)
	{
		theta += MathConstant::PI;
		theta -= floor(theta * (1.0f / (2 * MathConstant::PI))) * 2 * MathConstant::PI;
		theta -= MathConstant::PI;
		return theta;
	}

	static float Cos(float theta)
	{
		return cos(theta);
	}

	static float Sin(float theta)
	{
		return sin(theta);
	}

	static Matrix4x4 Euler2Matrix(const EulerAngles& qua)
	{
		float x = qua.x;
		float y = qua.y;
		float z = qua.z;
		float m00 = cos(qua.y) * cos(qua.z) + sin(qua.y) * sin(qua.x) * sin(qua.z);
		float m01 = sin(z) * cos(x);
		float m02 = -sin(y) * cos(z) + cos(y) * sin(x) * sin(z);

		float m10 = -cos(y) * sin(z) + sin(y) * sin(x) * cos(z);
		float m11 = cos(z) * cos(x);
		float m12 = sin(z) * sin(y) + cos(y) * sin(x) * cos(z);

		float m20 = sin(y) * cos(x);
		float m21 = -sin(x);
		float m22 = cos(y) * cos(x);

		return Matrix4x4(m00, m01, m02, 0,
			m10, m11, m12, 0,
			m20, m21, m22, 0,
			0, 0, 0, 1);
	}

	static Matrix4x4 MatrixInverse(const Matrix4x4& m)
	{
		float det = MatrixDet(m);
		Matrix4x4 adj = MatrixAdj(m);
		return adj / det;
	}

	static float MatrixDet(const Matrix4x4& m)
	{
		float result =
			m.m00 * Matrix3x3Det(m.m11, m.m12, m.m13, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33) -
			m.m10 * Matrix3x3Det(m.m01, m.m02, m.m03, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33) +
			m.m20 * Matrix3x3Det(m.m01, m.m02, m.m03, m.m11, m.m12, m.m13, m.m31, m.m32, m.m33) -
			m.m30 * Matrix3x3Det(m.m01, m.m02, m.m03, m.m11, m.m12, m.m13, m.m21, m.m22, m.m23);
		return result;
	}

	static Matrix4x4 MatrixAdj(const Matrix4x4& m)
	{
		float a00 = Matrix3x3Det(m.m11, m.m12, m.m13, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33);
		float a01 = Matrix3x3Det(m.m10, m.m12, m.m13, m.m20, m.m22, m.m23, m.m30, m.m32, m.m33);
		float a02 = Matrix3x3Det(m.m10, m.m11, m.m13, m.m20, m.m21, m.m23, m.m30, m.m31, m.m33);
		float a03 = Matrix3x3Det(m.m10, m.m11, m.m12, m.m20, m.m21, m.m22, m.m30, m.m31, m.m32);

		float a10 = Matrix3x3Det(m.m01, m.m02, m.m03, m.m21, m.m22, m.m23, m.m31, m.m32, m.m33);
		float a11 = Matrix3x3Det(m.m00, m.m02, m.m03, m.m20, m.m22, m.m23, m.m30, m.m32, m.m33);
		float a12 = Matrix3x3Det(m.m00, m.m01, m.m03, m.m20, m.m21, m.m23, m.m30, m.m31, m.m33);
		float a13 = Matrix3x3Det(m.m00, m.m01, m.m02, m.m20, m.m21, m.m22, m.m30, m.m31, m.m32);

		float a20 = Matrix3x3Det(m.m01, m.m02, m.m03, m.m11, m.m12, m.m13, m.m31, m.m32, m.m33);
		float a21 = Matrix3x3Det(m.m00, m.m02, m.m03, m.m10, m.m12, m.m13, m.m30, m.m32, m.m33);
		float a22 = Matrix3x3Det(m.m00, m.m01, m.m03, m.m10, m.m11, m.m13, m.m30, m.m31, m.m33);
		float a23 = Matrix3x3Det(m.m00, m.m01, m.m02, m.m10, m.m11, m.m12, m.m30, m.m31, m.m32);

		float a30 = Matrix3x3Det(m.m01, m.m02, m.m03, m.m11, m.m12, m.m13, m.m21, m.m22, m.m23);
		float a31 = Matrix3x3Det(m.m00, m.m02, m.m03, m.m10, m.m12, m.m13, m.m20, m.m22, m.m23);
		float a32 = Matrix3x3Det(m.m00, m.m01, m.m03, m.m10, m.m11, m.m13, m.m20, m.m21, m.m23);
		float a33 = Matrix3x3Det(m.m00, m.m01, m.m02, m.m10, m.m11, m.m12, m.m20, m.m21, m.m22);

		Matrix4x4 result(
			a00, -a01, a02, -a03,
			-a10, a11, -a12, a13,
			a20, -a21, a22, -a23,
			-a30, a31, -a32, a33);

		return MatrixTranspose(result);
	}

	static float Matrix3x3Det(
		float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22)
	{
		return
			m00 * (m11 * m22 - m21 * m12) -
			m10 * (m01 * m22 - m21 * m02) +
			m20 * (m01 * m12 - m11 * m02);
	}

	static Matrix4x4 MatrixTranspose(const Matrix4x4& m)
	{
		return Matrix4x4(
			m.m00, m.m10, m.m20, m.m30,
			m.m01, m.m11, m.m21, m.m31,
			m.m02, m.m12, m.m22, m.m23,
			m.m03, m.m13, m.m23, m.m33);
	}

	static VertexOut Lerp(const VertexOut& a, const VertexOut& b, float t)
	{
		return VertexOut(
			Lerp(a.pos, b.pos, t),
			Lerp(a.normal, b.normal, t),
			Lerp(a.uv, b.uv, t),
			Lerp(a.posH, b.posH, t),
			Lerp(a.color, b.color, t),
			Lerp(a.oneDivZ, b.oneDivZ, t)
			);		
	}

	static Vector4 Lerp(const Vector4& a, const Vector4& b, float t)
	{
		return Vector4(
			Lerp(a.x, b.x, t),
			Lerp(a.y, b.y, t),
			Lerp(a.z, b.z, t),
			a.w);
		return Vector4();
	}

	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
	{
		return Vector2(
			Lerp(a.x, b.x, t),
			Lerp(a.y, b.y, t));
	}

	static Color Lerp(const Color& a, const Color& b, float t)
	{
		return Color(
			Lerp(a.r, b.r, t),
			Lerp(a.g, b.g, t),
			Lerp(a.b, b.b, t),
			Lerp(a.a, b.a, t));
	}

	static float Lerp(const float& a, const float& b, float t)
	{
		return (1 - t) * a + t * b;
	}
private:

};
