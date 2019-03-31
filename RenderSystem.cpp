#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}
bool RenderSystem::Init(int width, int height) {
  m_width = width;
  m_height = height;
  frameBuffer = new UINT[width * height];
  memset(frameBuffer, 0, width * height * sizeof(UINT));

  zBuffer = new float[width * height];
  memset(zBuffer, 0, width*height * sizeof(float));
  return true;
}

void RenderSystem::Update(float deltaTime) {
    memset(frameBuffer, 0, m_width * m_height * sizeof(UINT));
    for (int i = 0;i<m_width;i++)
    {
      for (int j = 0; j<m_height;j++)
      {
        if (iBlack)
        {
          frameBuffer[i*m_height+j] = 0xFFFFFFFF;
        }
        else
        {
          frameBuffer[i*m_height + j] = 0;
        }
      }
    }
    iBlack = !iBlack;
}