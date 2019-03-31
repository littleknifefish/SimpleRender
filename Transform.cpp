#include "Transform.h"
#include "Math/Math.h"
using namespace MathConstant;

mat4 Transform::Rotate(const float degree, Vector4& axis) {
  float rad = degree * PI / 180;
  Vector4 axisNor = Vector4::Normalize(axis);
  mat4 K = mat4(0, axisNor.z, -axisNor.y, 0,
    axisNor.y, 0, axisNor.x, 0, 
    axisNor.y, -axisNor.x, 0, 0,
    0,0,0,1);
  mat4 squareK = K * K;
  mat4 I(1.0);
  return I + K * sin(rad) + squareK * (1 - Mathf::Cos(rad));
}

mat4 Transform::Lookat(Vector4& eye, Vector4& up) {
  Vector4 w = Vector4::Normalize(eye);
  Vector4 u = Vector4::Normalize(Vector4::CrossProduct(up, w));
  Vector4 v = Vector4::Normalize(Vector4::CrossProduct(w, u));

  return mat4(u.x, u.y, u.z, 0,
    v.x, v.y, v.z, 0,
    w.x, w.y, w.z, 0,
    0, 0, 0, 1);
}



Transform::Transform()
{
}

Transform::~Transform()
{
}