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
//  //˫�����ͼ
//  static BITMAPINFO s_bitmapInfo;
//  static HDC s_hdcBackbuffer;		//�󻺳��豸���	
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
//    //  //�����󻺳���
//    //  //�ȴ���һ���ڴ�dc
//    //  s_hdcBackbuffer = CreateCompatibleDC(nullptr);
//    //  //���ǰ�û�����dc
//    //  HDC hdc = GetDC(hwnd);
//    //  if (!(s_hBitmap = CreateDIBSection(nullptr, (PBITMAPINFO)&bmphdr, DIB_RGB_COLORS,
//    //    reinterpret_cast<void**>(&SEngine::GetInstance()->renderSystem->frameBuffer), nullptr, 0)))
//    //  {
//    //    MessageBox(nullptr, L"create dib section failed!", L"error", MB_OK);
//    //    return 0;
//    //  }
//    //  //��bitmapװ���ڴ�dc
//    //  s_hOldBitmap = (HBITMAP)SelectObject(s_hdcBackbuffer, s_hBitmap);
//    //  //�ͷ�dc
//    //  ReleaseDC(hwnd, hdc);
//    //  break;
//    //}
//  case WM_PAINT: 
//    //Ҫ���� WM_PAINT ��Ϣ������Ӧ���� BeginPaint
//    //Ȼ�������е��߼��Լ��ڴ����в����ı�����ť�������ؼ���
//    //Ȼ����� EndPaint�� 
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
//    // -----------------����δ����Ӧ�ó�����в���------------------------ 
//    // ���ڴ�Ӧ�ó��򣬿�ʼ���úͽ�������֮����߼����ڴ�������ʾ�ַ��� ��Hello��World!����
//    // ��ע�� TextOut ����������ʾ�ַ�����
//    TextOut(hdc, 50, 5, greeting, _tcslen(greeting));
//    // -----------------------����ģ�����----------------------------------
//
//    EndPaint(hWnd, &ps);
//    break;
//  case WM_DESTROY:
//    PostQuitMessage(0);
//    break;
//  default:
//    //DefWindowProcȱʡ���ڴ�����
//    //���������Ĭ�ϵĴ��ڴ����������ǿ��԰Ѳ����ĵ���Ϣ��������������
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

  //˫�����ͼ
  static BITMAPINFO s_bitmapInfo;
  static HDC s_hdcBackbuffer;		//�󻺳��豸���	
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
    //�����󻺳���
    //�ȴ���һ���ڴ�dc
    s_hdcBackbuffer = CreateCompatibleDC(nullptr);
    //���ǰ�û�����dc
    HDC hdc = GetDC(hwnd);
    if (!(s_hBitmap = CreateDIBSection(nullptr, (PBITMAPINFO)&bmphdr, DIB_RGB_COLORS,
      reinterpret_cast<void**>(&Engine::GetInstance()->renderSystem->frameBuffer), nullptr, 0)))
    {
      MessageBox(nullptr, _T("create dib section failed!"), _T("error"), MB_OK);
      return 0;
    }
    //��bitmapװ���ڴ�dc
    s_hOldBitmap = (HBITMAP)SelectObject(s_hdcBackbuffer, s_hBitmap);
    //�ͷ�dc
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