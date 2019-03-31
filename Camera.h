#pragma once
#include "Math/Vector4.h"
#include "Math/Matrix4x4.h"

class Camera
{
public:
  Camera();
  ~Camera();

  void UpdateViewMat();
  void UpdateProjMat();

  float m_flov;
 // Vector4 m_pos;
  float m_nearZ;
  float m_farZ;
  float m_aspect;
  Vector4 m_up;
  Matrix4x4 m_viewMat; 
  Matrix4x4 m_perMat;
private:

};
