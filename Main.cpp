//#include <windows.h> 
#include <stdlib.h> 
#include <string.h> 
#include <tchar.h> 
#include "App.h"
#include "Engine.h"


static TCHAR szWindowClass[] = _T("win32app");
// 应用程序标题栏处出现的字符串
static TCHAR szTitle[] = _T("Soft Render Test");

HINSTANCE hInst;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int g_width = 800;
int g_height = 480;

App* m_app;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  //创建 WNDCLASSEX 类型的窗口类结构。 此结构包含关于窗口的信息
  //例如应用程序图标、窗口背景色、标题栏中显示的名称、窗口过程函数的名称等。
  m_app = new App();

  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

  //对已创建的窗口类进行注册。 使用 RegisterClassEx 函数，并将窗口类结构作为参数传递。
  if (!RegisterClassEx(&wcex)) {
    MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Win32 Guided Tour"), NULL);
    return 1;
  }

  // Store instance handle in our global variable 
  // 将句柄实例存储于全局变量中
  hInst = hInstance;
  m_app->init(hInst, g_width, g_height);

  // CreateWindow 函数的参数解释: 
  // szWindowClass: the name of the application 
  // szTitle: the text that appears in the title bar 
  // WS_OVERLAPPEDWINDOW: the type of window to create 
  // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y) 
  // 500, 100: initial size (width, length) 
  // NULL: the parent of this window 
  // NULL: this application does not have a menu bar 
  // hInstance: the first parameter from WinMain 
  // NULL: not used in this application 
  // 返回的HWND是一个窗口的句柄
  HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, g_width, g_height, NULL, NULL, hInstance, NULL);
  if (!hWnd) {
    MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Win32 Guided Tour"), NULL);
    return 1;
  }

  MoveWindow(hWnd, 250, 250, g_width, g_height, true);
  // ShowWindow 函数的参数解释: 
  // hWnd: CreateWindow函数返回的窗口句柄 
  // nCmdShow: the fourth parameter from WinMain 
  ShowWindow(hWnd, nCmdShow);
  // UpdateWindow函数用于更新窗口指定的区域
  // 如果窗口更新的区域不为空，UpdateWindow函数就发送一个WM_PAINT消息来更新指定窗口的客户区。
  // 函数绕过应用程序的消息队列，直接发送WM_PAINT消息给指定窗口的窗口过程
  // 如果更新区域为空，则不发送消息。
  UpdateWindow(hWnd);
  
  return m_app->run();

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  return m_app->MsgProc(hWnd, message, wParam, lParam);
  //PAINTSTRUCT ps;
  //HDC hdc;
  //static TCHAR greeting[] = _T("Hello, World!");

  ////双缓冲绘图
  //static BITMAPINFO s_bitmapInfo;
  //static HDC s_hdcBackbuffer;		//后缓冲设备句柄	
  //static HBITMAP s_hBitmap;
  //static HBITMAP s_hOldBitmap;
  //static void* s_pData;

  //switch (message) {
  //case WM_CREATE:
  //{
  //  //  m_mainWnd = hWnd;
  //  //  BITMAPINFOHEADER bmphdr = { 0 };
  //  //  bmphdr.biSize = sizeof(BITMAPINFOHEADER);
  //  //  bmphdr.biWidth = g_width;
  //  //  bmphdr.biHeight = -g_height;
  //  //  bmphdr.biPlanes = 1;
  //  //  bmphdr.biBitCount = 32;
  //  //  bmphdr.biSizeImage = g_width * g_height * 4;
  //  //  //创建后缓冲区
  //  //  //先创建一个内存dc
  //  //  s_hdcBackbuffer = CreateCompatibleDC(nullptr);
  //  //  //获得前置缓冲区dc
  //  //  HDC hdc = GetDC(hwnd);
  //  //  if (!(s_hBitmap = CreateDIBSection(nullptr, (PBITMAPINFO)&bmphdr, DIB_RGB_COLORS,
  //  //    reinterpret_cast<void**>(&SEngine::GetInstance()->renderSystem->frameBuffer), nullptr, 0)))
  //  //  {
  //  //    MessageBox(nullptr, L"create dib section failed!", L"error", MB_OK);
  //  //    return 0;
  //  //  }
  //  //  //将bitmap装入内存dc
  //  //  s_hOldBitmap = (HBITMAP)SelectObject(s_hdcBackbuffer, s_hBitmap);
  //  //  //释放dc
  //  //  ReleaseDC(hwnd, hdc);
  //  //  break;
  //  //}
  //case WM_PAINT:
  //  //要处理 WM_PAINT 消息，首先应调用 BeginPaint
  //  //然后处理所有的逻辑以及在窗口中布局文本、按钮和其他控件等
  //  //然后调用 EndPaint。 

  //  //hdc = BeginPaint(hWnd, &ps);
  //  //BitBlt(ps.hdc, 0, 0, g_width, g_height, s_hdcBackbuffer, 0, 0, SRCCOPY);
  //  //EndPaint(hWnd, &ps);

  //  hdc = BeginPaint(hWnd, &ps);
  //  if (greeting[0] == WCHAR("H")) {
  //    greeting[0] = WCHAR("h");
  //  }
  //  else
  //  {
  //    greeting[0] = WCHAR("H");
  //  }
  //  // -----------------在这段代码对应用程序进行布局------------------------ 
  //  // 对于此应用程序，开始调用和结束调用之间的逻辑是在窗口中显示字符串 “Hello，World!”。
  //  // 请注意 TextOut 函数用于显示字符串。
  //  TextOut(hdc, 50, 5, greeting, _tcslen(greeting));
  //  // -----------------------布局模块结束----------------------------------

  //  EndPaint(hWnd, &ps);
  //  break;
  //case WM_DESTROY:
  //  PostQuitMessage(0);
  //  break;
  //default:
  //  //DefWindowProc缺省窗口处理函数
  //  //这个函数是默认的窗口处理函数，我们可以把不关心的消息都丢给它来处理
  //  return DefWindowProc(hWnd, message, wParam, lParam);
  //  break;
  //}
  //return 0;
  //}

}
