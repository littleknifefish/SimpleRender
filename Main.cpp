//#include <windows.h> 
#include <stdlib.h> 
#include <string.h> 
#include <tchar.h> 
#include "App.h"
#include "Engine.h"


static TCHAR szWindowClass[] = _T("win32app");
// Ӧ�ó�������������ֵ��ַ���
static TCHAR szTitle[] = _T("Soft Render Test");

HINSTANCE hInst;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int g_width = 800;
int g_height = 480;

App* m_app;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  //���� WNDCLASSEX ���͵Ĵ�����ṹ�� �˽ṹ�������ڴ��ڵ���Ϣ
  //����Ӧ�ó���ͼ�ꡢ���ڱ���ɫ������������ʾ�����ơ����ڹ��̺��������Ƶȡ�
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

  //���Ѵ����Ĵ��������ע�ᡣ ʹ�� RegisterClassEx ����������������ṹ��Ϊ�������ݡ�
  if (!RegisterClassEx(&wcex)) {
    MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Win32 Guided Tour"), NULL);
    return 1;
  }

  // Store instance handle in our global variable 
  // �����ʵ���洢��ȫ�ֱ�����
  hInst = hInstance;
  m_app->init(hInst, g_width, g_height);

  // CreateWindow �����Ĳ�������: 
  // szWindowClass: the name of the application 
  // szTitle: the text that appears in the title bar 
  // WS_OVERLAPPEDWINDOW: the type of window to create 
  // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y) 
  // 500, 100: initial size (width, length) 
  // NULL: the parent of this window 
  // NULL: this application does not have a menu bar 
  // hInstance: the first parameter from WinMain 
  // NULL: not used in this application 
  // ���ص�HWND��һ�����ڵľ��
  HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, g_width, g_height, NULL, NULL, hInstance, NULL);
  if (!hWnd) {
    MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Win32 Guided Tour"), NULL);
    return 1;
  }

  MoveWindow(hWnd, 250, 250, g_width, g_height, true);
  // ShowWindow �����Ĳ�������: 
  // hWnd: CreateWindow�������صĴ��ھ�� 
  // nCmdShow: the fourth parameter from WinMain 
  ShowWindow(hWnd, nCmdShow);
  // UpdateWindow�������ڸ��´���ָ��������
  // ������ڸ��µ�����Ϊ�գ�UpdateWindow�����ͷ���һ��WM_PAINT��Ϣ������ָ�����ڵĿͻ�����
  // �����ƹ�Ӧ�ó������Ϣ���У�ֱ�ӷ���WM_PAINT��Ϣ��ָ�����ڵĴ��ڹ���
  // �����������Ϊ�գ��򲻷�����Ϣ��
  UpdateWindow(hWnd);
  
  return m_app->run();

}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  return m_app->MsgProc(hWnd, message, wParam, lParam);
  //PAINTSTRUCT ps;
  //HDC hdc;
  //static TCHAR greeting[] = _T("Hello, World!");

  ////˫�����ͼ
  //static BITMAPINFO s_bitmapInfo;
  //static HDC s_hdcBackbuffer;		//�󻺳��豸���	
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
  //  //  //�����󻺳���
  //  //  //�ȴ���һ���ڴ�dc
  //  //  s_hdcBackbuffer = CreateCompatibleDC(nullptr);
  //  //  //���ǰ�û�����dc
  //  //  HDC hdc = GetDC(hwnd);
  //  //  if (!(s_hBitmap = CreateDIBSection(nullptr, (PBITMAPINFO)&bmphdr, DIB_RGB_COLORS,
  //  //    reinterpret_cast<void**>(&SEngine::GetInstance()->renderSystem->frameBuffer), nullptr, 0)))
  //  //  {
  //  //    MessageBox(nullptr, L"create dib section failed!", L"error", MB_OK);
  //  //    return 0;
  //  //  }
  //  //  //��bitmapװ���ڴ�dc
  //  //  s_hOldBitmap = (HBITMAP)SelectObject(s_hdcBackbuffer, s_hBitmap);
  //  //  //�ͷ�dc
  //  //  ReleaseDC(hwnd, hdc);
  //  //  break;
  //  //}
  //case WM_PAINT:
  //  //Ҫ���� WM_PAINT ��Ϣ������Ӧ���� BeginPaint
  //  //Ȼ�������е��߼��Լ��ڴ����в����ı�����ť�������ؼ���
  //  //Ȼ����� EndPaint�� 

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
  //  // -----------------����δ����Ӧ�ó�����в���------------------------ 
  //  // ���ڴ�Ӧ�ó��򣬿�ʼ���úͽ�������֮����߼����ڴ�������ʾ�ַ��� ��Hello��World!����
  //  // ��ע�� TextOut ����������ʾ�ַ�����
  //  TextOut(hdc, 50, 5, greeting, _tcslen(greeting));
  //  // -----------------------����ģ�����----------------------------------

  //  EndPaint(hWnd, &ps);
  //  break;
  //case WM_DESTROY:
  //  PostQuitMessage(0);
  //  break;
  //default:
  //  //DefWindowProcȱʡ���ڴ�����
  //  //���������Ĭ�ϵĴ��ڴ����������ǿ��԰Ѳ����ĵ���Ϣ��������������
  //  return DefWindowProc(hWnd, message, wParam, lParam);
  //  break;
  //}
  //return 0;
  //}

}
