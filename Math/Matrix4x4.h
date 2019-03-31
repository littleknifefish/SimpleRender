#pragma once
struct Matrix4x4
{
public:
	union
	{
		float m[4][4];
		struct
		{
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
	};
	
public:
	Matrix4x4() = default;
        Matrix4x4(float m) :m00(m), m01(0), m02(0), m03(0),
          m10(0), m11(m), m12(0), m13(0),
          m20(0), m21(0), m22(m), m23(0),
          m30(0), m31(0), m32(0), m33(m) 
        {
        }

	Matrix4x4(float m00,float m01,float m02,float m03,
			  float m10,float m11,float m12,float m13,
			  float m20,float m21,float m22,float m23,
			  float m30,float m31,float m32,float m33)
		:m00(m00),m01(m01),m02(m02),m03(m03),
		 m10(m10),m11(m11),m12(m12),m13(m13),
		 m20(m20),m21(m21),m22(m22),m23(m23),
		 m30(m30),m31(m31),m32(m32),m33(m33)
	{
	}
	~Matrix4x4(){}

	Matrix4x4 operator * (const Matrix4x4& other)
	{
		Matrix4x4 mat;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat.m[i][j] = (m[i][0] * other.m[0][j]) +
					(m[i][1] * other.m[1][j]) +
					(m[i][2] * other.m[2][j]) +
					(m[i][3] * other.m[3][j]);
			}
		}
		return mat;
	}

        Matrix4x4 operator * (const float num)
        {
          Matrix4x4 mat;
          for (int i = 0; i < 4; i++)
          {
            for (int j = 0; j < 4; j++)
            {
              mat.m[i][j] *= num;
            }
          }
          return mat;
        }

        Matrix4x4 operator + (const Matrix4x4& other)
        {
          Matrix4x4 mat;
          for (int i = 0; i < 4; i++)
          {
            for (int j = 0; j < 4; j++)
            {
              mat.m[i][j] += other.m[i][j];
            }
          }
          return mat;
        }

	Matrix4x4 operator / (const float& a)
	{
		Matrix4x4 m;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m.m[i][j] = this->m[i][j] / 4;
			}
		}
		return m;
	}

	void SetZero()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] = 0.0f;
			}
		}
	}
};

