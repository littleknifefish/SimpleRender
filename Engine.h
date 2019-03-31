#pragma once
#include "RenderSystem.h"

extern WCHAR greeting[20];// = _T("Hello, World!");
//static WCHAR s_greeting[];

class Engine {
public:
  static Engine* GetInstance();
  int update();
  
  int Init(int w, int h);

  int Run();
  RenderSystem* renderSystem;
};