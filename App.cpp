#include "App.h"

int App::init(HINSTANCE hWnd, int w, int h) {
  m_appInst = hWnd;
  m_width = w;
  m_height = h;

  Engine::GetInstance()->Init(m_width, m_height);

  return 0;
}

//LRESULT App::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//  PAINTSTRUCT ps;
//  HDC hdc;
//
//  //双缓冲绘图
//  static BITMAPINFO s_bitmapInfo;
//  static HDC s_hdcBackbuffer;		//后缓冲设备句柄	
//  static HBITMAP s_hBitmap;
//  static HBITMAP s_hOldBitmap;
//  static void* s_pData;
//
//  switch (message) {
//  case WM_CREATE:
//  {
//      m_mainWnd = hWnd;
//    //  BITMAPINFOHEADER bmphdr = { 0 };
//    //  bmphdr.biSize = sizeof(BITMAPINFOHEADER);
//    //  bmphdr.biWidth = g_width;
//    //  bmphdr.biHeight = -g_height;
//    //  bmphdr.biPlanes = 1;
//    //  bmphdr.biBitCount = 32;
//    //  bmphdr.biSizeImage = g_width * g_height * 4;
//    //  //创建后缓冲区
//    //  //先创建一个内存dc
//    //  s_hdcBackbuffer = CreateCompatibleDC(nullptr);
//    //  //获得前置缓冲区dc
//    //  HDC hdc = GetDC(hwnd);
//    //  if (!(s_hBitmap = CreateDIBSection(nullptr, (PBITMAPINFO)&bmphdr, DIB_RGB_COLORS,
//    //    reinterpret_cast<void**>(&SEngine::GetInstance()->renderSystem->frameBuffer), nullptr, 0)))
//    //  {
//    //    MessageBox(nullptr, L"create dib section failed!", L"error", MB_OK);
//    //    return 0;
//    //  }
//    //  //将bitmap装入内存dc
//    //  s_hOldBitmap = (HBITMAP)SelectObject(s_hdcBackbuffer, s_hBitmap);
//    //  //释放dc
//    //  ReleaseDC(hwnd, hdc);
//    //  break;
//    //}
//  case WM_PAINT: 
//    //要处理 WM_PAINT 消息，首先应调用 BeginPaint
//    //然后处理所有的逻辑以及在窗口中布局文本、按钮和其他控件等
//    //然后调用 EndPaint。 
//
//    //hdc = BeginPaint(hWnd, &ps);
//    //BitBlt(ps.hdc, 0, 0, g_width, g_height, s_hdcBackbuffer, 0, 0, SRCCOPY);
//    //EndPaint(hWnd, &ps);
//
//    hdc = BeginPaint(hWnd, &ps);
//    //if (greeting[0] == WCHAR("H")) {
//    //  greeting[0] = WCHAR("h");
//    //}
//    //else
//    //{
//    //  greeting[0] = WCHAR("H");
//    //}
//    // -----------------在这段代码对应用程序进行布局------------------------ 
//    // 对于此应用程序，开始调用和结束调用之间的逻辑是在窗口中显示字符串 “Hello，World!”。
//    // 请注意 TextOut 函数用于显示字符串。
//    TextOut(hdc, 50, 5, greeting, _tcslen(greeting));
//    // -----------------------布局模块结束----------------------------------
//
//    EndPaint(hWnd, &ps);
//    break;
//  case WM_DESTROY:
//    PostQuitMessage(0);
//    break;
//  default:
//    //DefWindowProc缺省窗口处理函数
//    //这个函数是默认的窗口处理函数，我们可以把不关心的消息都丢给它来处理
//    return DefWindowProc(hWnd, message, wParam, lParam);
//    break;
//  }
//  return 0;
//  }
//  return 0;
//}


LRESULT App::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;

  //双缓冲绘图
  static BITMAPINFO s_bitmapInfo;
  static HDC s_hdcBackbuffer;		//后缓冲设备句柄	
  static HBITMAP s_hBitmap;
  static HBITMAP s_hOldBitmap;
  static void* s_pData;

  switch (msg)
  {
  case WM_CREATE:
  {
    m_mainWnd = hwnd;
    BITMAPINFOHEADER bmphdr = { 0 };
    bmphdr.biSize = sizeof(BITMAPINFOHEADER);
    bmphdr.biWidth = m_width;
    bmphdr.biHeight = -m_height;
    bmphdr.biPlanes = 1;
    bmphdr.biBitCount = 32;
    bmphdr.biSizeImage = m_width * m_height * 4;
    //创建后缓冲区
    //先创建一个内存dc
    s_hdcBackbuffer = CreateCompatibleDC(nullptr);
    //获得前置缓冲区dc
    HDC hdc = GetDC(hwnd);
    if (!(s_hBitmap = CreateDIBSection(nullptr, (PBITMAPINFO)&bmphdr, DIB_RGB_COLORS,
      reinterpret_cast<void**>(&Engine::GetInstance()->renderSystem->frameBuffer), nullptr, 0)))
    {
      MessageBox(nullptr, _T("create dib section failed!"), _T("error"), MB_OK);
      return 0;
    }
    //将bitmap装入内存dc
    s_hOldBitmap = (HBITMAP)SelectObject(s_hdcBackbuffer, s_hBitmap);
    //释放dc
    ReleaseDC(hwnd, hdc);
  }
  break;
  case WM_SIZE:
  {

  }
  case WM_ERASEBKGND:
    return true;
    break;
  case WM_PAINT:
  {
    //WCHAR outStr[] = _T("Show ");
    //OutputDebugString(outStr);
    //OutputDebugString(greeting);
    //OutputDebugString((LPCTSTR)"\n");


    hdc = BeginPaint(hwnd, &ps);
    BitBlt(ps.hdc, 0, 0, m_width, m_height, s_hdcBackbuffer, 0, 0, SRCCOPY);

   // TextOut(hdc, 50, 5, greeting, _tcslen(greeting));

    EndPaint(hwnd, &ps);
    //SEngine::GetInstance()->renderSystem->ClearFrameBuffer();
    break;
  }

  break;
  default:
    return DefWindowProc(hwnd, msg, wParam, lParam);
    break;
  }
  return 0;
}


int App::run() {
  MSG msg = { 0 };
  ZeroMemory(&msg, sizeof(msg));
  while (msg.message != WM_QUIT)
  {
    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      int result = Engine::GetInstance()->Run();

      InvalidateRect(m_mainWnd, nullptr, true);
      UpdateWindow(m_mainWnd);

      if (result != 0)
      {
        return result;
      }
    }
  }
  return (int)msg.wParam;
}

App::App()
{
}

App::~App()
{
}