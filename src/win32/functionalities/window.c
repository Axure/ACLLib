//
// Created by Colliot on 2016/9/6.
//
#include "acllib.h"
#include "window.h"
#include "../global.h"
#include <stdio.h>
#include <stdlib.h>

HINSTANCE g_hInstance;

HWND g_hWnd = NULL;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//
void acl_error(char *errStr) {
  MessageBoxA(g_hWnd, errStr, g_libName, MB_ICONERROR);
  exit(0);
}

//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
  MSG msg;
  WNDCLASSA wndclass;

  g_hInstance = hInstance;
  g_hWnd = NULL;
  g_keyboard = NULL;
  g_mouse = NULL;
  g_timer = NULL;

  wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
  wndclass.lpfnWndProc = WndProc;
  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;
  wndclass.hInstance = hInstance;
  wndclass.hInstance = hInstance;
  wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
  wndclass.lpszMenuName = NULL;
  wndclass.lpszClassName = g_wndClassName;

  if (!RegisterClassA(&wndclass)) {
    MessageBoxA(NULL, "This program requires Windows NT!", g_libName, MB_ICONERROR);
    return 0;
  }

  Setup();

  ACL_ASSERT(g_hWnd, "You must call \"initWindow(...)\" in Main()");

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

//
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_CREATE: {
      HDC hdc;
      hdc = GetDC(hwnd);
      g_HBITMAP = CreateCompatibleBitmap(
          hdc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
      g_hmemdc = CreateCompatibleDC(hdc);
      SelectObject(g_hmemdc, g_HBITMAP);
      BitBlt(g_hmemdc,
             0, 0,
             GetSystemMetrics(SM_CXSCREEN),
             GetSystemMetrics(SM_CYSCREEN),
             g_hmemdc,
             0, 0,
             WHITENESS);
      DeleteDC(g_hmemdc);
      ReleaseDC(hwnd, hdc);

      CreateCaret(hwnd, 0, g_caretWidth, g_caretHeight);
      g_caretX = g_wndWidth;
      g_caretY = g_wndHeight;
      SetCaretPos(g_caretX, g_caretY);

      break;
    }
    case WM_ERASEBKGND:
      break;
    case WM_PAINT: {
      HDC hdc;
      PAINTSTRUCT ps;
      RECT rect;

      hdc = BeginPaint(hwnd, &ps);
      g_hmemdc = CreateCompatibleDC(hdc);
      SelectObject(g_hmemdc, g_HBITMAP);
      GetClientRect(hwnd, &rect);
      BitBlt(hdc, 0, 0, rect.right - rect.left,
             rect.bottom - rect.top, g_hmemdc, 0, 0, SRCCOPY);
      DeleteDC(g_hmemdc);
      g_hmemdc = 0;
      EndPaint(hwnd, &ps);
      break;
    }
    case WM_CHAR:
      if (g_char != NULL)
        g_char((char) wParam);
      break;

    case WM_KEYDOWN:
      if (g_keyboard != NULL)
        g_keyboard((int) wParam, KEY_DOWN);
      break;

    case WM_KEYUP:
      if (g_keyboard != NULL)
        g_keyboard((int) wParam, KEY_UP);
      break;

    case WM_LBUTTONDOWN:
      if (g_mouse != NULL)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), LEFT_BUTTON, BUTTON_DOWN);
      break;

    case WM_LBUTTONUP:
      if (g_mouse != NULL)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), LEFT_BUTTON, BUTTON_UP);
      break;

    case WM_LBUTTONDBLCLK:
      if (g_mouse != NULL)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), LEFT_BUTTON, BUTTON_DOUBLECLICK);
      break;

    case WM_MBUTTONDOWN:
      if (g_mouse != NULL)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MIDDLE_BUTTON, BUTTON_DOWN);
      break;

    case WM_MBUTTONUP:
      if (g_mouse != NULL)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MIDDLE_BUTTON, BUTTON_UP);
      break;

    case WM_MBUTTONDBLCLK:
      if (g_mouse != NULL)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MIDDLE_BUTTON, BUTTON_DOUBLECLICK);
      break;

    case WM_RBUTTONDOWN:
      if (g_mouse != NULL)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), RIGHT_BUTTON, BUTTON_DOWN);
      break;

    case WM_RBUTTONUP:
      if (g_mouse != NULL)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), RIGHT_BUTTON, BUTTON_UP);
      break;

    case WM_RBUTTONDBLCLK:
      if (g_mouse != NULL)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), RIGHT_BUTTON, BUTTON_DOUBLECLICK);
      break;

    case WM_MOUSEMOVE:
      if (g_mouse != NULL)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MOUSEMOVE, MOUSEMOVE);
      break;

    case WM_MOUSEWHEEL:
      if (g_mouse == NULL)
        break;
      if (HIWORD(wParam) == 120)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MIDDLE_BUTTON, ROLL_UP);
      else if (HIWORD(wParam) == 65416)
        g_mouse((int) LOWORD(lParam), (int) HIWORD(lParam), MIDDLE_BUTTON, ROLL_DOWN);
      break;

    case WM_TIMER:
      if (g_timer != NULL)
        g_timer(wParam);
      break;

    case WM_DESTROY:
      DeleteObject(g_HBITMAP);
      PostQuitMessage(0);
      break;
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
  }
  return 0;
}


int g_wndHeight;
int g_wndWidth;
const char g_wndClassName[] = "ACL_WND_CLASS";
const char g_libName[] = "ACLLIB";

//
void initWindow(const char *wndName, int x, int y, int width, int height) {
  RECT rect;

  ACL_ASSERT(!g_hWnd, "Don't call initWindow twice");

  g_wndHeight = height;
  g_wndWidth = width;

  if (x == DEFAULT || y == DEFAULT)
    x = y = CW_USEDEFAULT;

  g_hWnd = CreateWindowA (
      g_wndClassName, wndName,
      WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX,
      x, y,
      width, height,
      NULL, NULL, 0, NULL);

  if (!g_hWnd) {
    MessageBoxA(NULL, "Fail to create window", g_libName, MB_ICONERROR);
    exit(0);
  }
  GetClientRect(g_hWnd, &rect);
  width += width - (rect.right - rect.left);
  height += height - (rect.bottom - rect.top);
  SetWindowPos(g_hWnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE);

  ShowWindow(g_hWnd, 1);
  UpdateWindow(g_hWnd);
}

void initConsole(void) {
  AllocConsole();
  freopen("CONIN$", "r+t", stdin);
  freopen("CONOUT$", "w+t", stdout);
}

void msgBox(const char title[], const char text[], int flag) {
  ACL_ASSERT_HWND;
  MessageBoxA(g_hWnd, text, title, flag);
}

