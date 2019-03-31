#pragma once
#include "Math/Matrix4x4.h"
#include "Math/Vector4.h"

#define mat4 Matrix4x4
class Transform
{
public:
  Transform();
  ~Transform();

  mat4 Rotate(const float degree, Vector4& axis);

  /*Ä¬ÈÏcenterÔÚ£¨0,0,0£©*/
  mat4 Lookat(Vector4& eye, Vector4& up);

  mat4 Perspective();
private:

};
