#include "Engine.h"

using namespace std;

//WCHAR greeting[20] = _T("Hello, World!");
//extern WCHAR s_greeting[10];// = _T("Static Hello, World!");

Engine* Engine::GetInstance() {
  static Engine* instance =  new Engine();
  return instance;
}

int Engine::Init(int w, int h) {
  renderSystem = new RenderSystem();
  renderSystem->Init(w, h);
  return 0;
}

int Engine::update() {
  static ULONGLONG _time_delta = 0;
  static ULONGLONG _time_start = 0;

  ULONGLONG _time_cur = 0;

  _time_cur = GetTickCount64();
  if (_time_start == 0) {
    _time_start = _time_cur;
  }

  _time_delta += _time_cur - _time_start;
  _time_start = _time_cur;
  
  if (_time_delta > 1000)
  {
    renderSystem->Update(_time_delta);

   /* if (greeting[0] == 'H') {
      greeting[0] = 'h';
    }
    else
    {
      greeting[0] = 'H';
    }

    WCHAR outStr[] = _T("Changed to ");
    OutputDebugString(outStr);
    OutputDebugString(greeting);
    OutputDebugString((LPCTSTR)"\n");*/

    _time_delta = 0;
  }
  return 0;
}

int Engine::Run() {
  update();
  return 0;
}