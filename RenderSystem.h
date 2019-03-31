#pragma once
#include <wtypes.h>

static bool iBlack = true;
class RenderSystem
{
public:
  RenderSystem();
  ~RenderSystem();

  UINT* frameBuffer;
  float* zBuffer;
  
  bool Init(int width, int height);
  void RebuildFrameBuffer(int width, int height);

  void Update(float deltaTime);
private:
  int m_width;
  int m_height;
};
