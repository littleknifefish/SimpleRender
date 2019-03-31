#pragma once
//#include <windows.h>
#include <wtypes.h>
#include <winuser.h>
//#include <winnt.h>
#include <tchar.h>
#include "Engine.h"

class App
{
public:
  App();
  ~App();

  int init(HINSTANCE hWnd, int w, int h);
  int run();

  LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
  HINSTANCE m_appInst;;
  HWND m_mainWnd;
  int m_width;
  int m_height;
};