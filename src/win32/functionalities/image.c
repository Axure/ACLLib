//
// Created by Colliot on 2016/9/6.
//

#include "../global.h"
#include "./window.h"
#include "functionalities/image.h"
#include <windows.h>
#include <olectl.h>

extern HDC g_hmemdc;

void putImage(ACL_Image *pImage, int x, int y) {
  HDC HBITMAPdc;
  ACL_ASSERT_BEGIN_PAINT;
  HBITMAPdc = CreateCompatibleDC(g_hmemdc);
  SelectObject(HBITMAPdc, pImage->HBITMAP);
  BitBlt(g_hmemdc, x, y, pImage->width, pImage->height, HBITMAPdc, 0, 0, SRCCOPY);
  DeleteDC(HBITMAPdc);
}

void putImageScale(ACL_Image *pImage, int x, int y, int width, int height) {
  HDC HBITMAPdc;
  ACL_ASSERT_BEGIN_PAINT;
  HBITMAPdc = CreateCompatibleDC(g_hmemdc);
  SelectObject(HBITMAPdc, pImage->HBITMAP);
  if (width == -1)width = pImage->width;
  if (height == -1)height = pImage->height;
  SetStretchBltMode(g_hmemdc, COLORONCOLOR);
  StretchBlt(g_hmemdc, x, y, width, height, HBITMAPdc, 0, 0, pImage->width, pImage->height, SRCCOPY);
  DeleteDC(HBITMAPdc);
}

void putImageTransparent(ACL_Image *pImage, int x, int y, int width, int height, ACL_Color bkColor) {
  HDC HBITMAPdc;
  ACL_ASSERT_BEGIN_PAINT;
  HBITMAPdc = CreateCompatibleDC(g_hmemdc);
  SelectObject(HBITMAPdc, pImage->HBITMAP);
  if (width == -1)width = pImage->width;
  if (height == -1)height = pImage->height;
  //SetStretchBltMode(g_hmemdc,COLORONCOLOR);
  TransparentBlt(g_hmemdc, x, y, width, height, HBITMAPdc, 0, 0, pImage->width, pImage->height, bkColor);
  DeleteDC(HBITMAPdc);
}

void loadImage(const char *image, ACL_Image *mapbuf) {
  HDC hmapdc;
  IPicture *ipicture;
  IStream *istream;
  DWORD filesize = 0, bytes;
  OLE_XSIZE_HIMETRIC width;
  OLE_YSIZE_HIMETRIC height;
  HANDLE file = NULL;
  HGLOBAL global = NULL;
  LPVOID data = NULL;

  ACL_ASSERT_HWND;

  file = CreateFileA(image, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (file == INVALID_HANDLE_VALUE)
    acl_error("Fail to load image, File not exist");
  filesize = GetFileSize(file, NULL);

  global = GlobalAlloc(GMEM_MOVEABLE, filesize);
  data = GlobalLock(global);
  ReadFile(file, data, filesize, &bytes, NULL);
  GlobalUnlock(global);
  CreateStreamOnHGlobal(global, TRUE, &istream);

  OleLoadPicture(istream, filesize, TRUE, &IID_IPicture, (LPVOID *) &ipicture);
  ipicture->lpVtbl->get_Width(ipicture, &width);
  ipicture->lpVtbl->get_Height(ipicture, &height);

  mapbuf->width = (int) (width / 26.45833333333);
  mapbuf->height = (int) (height / 26.45833333333);

  hmapdc = CreateCompatibleDC(GetDC(g_hWnd));
  if (mapbuf->HBITMAP != NULL)
    DeleteObject(mapbuf->HBITMAP);
  mapbuf->HBITMAP = CreateCompatibleBitmap(GetDC(g_hWnd), mapbuf->width, mapbuf->height);
  SelectObject(hmapdc, mapbuf->HBITMAP);

  ipicture->lpVtbl->Render(ipicture, hmapdc, 0, 0, mapbuf->width, mapbuf->height, 0, height, width, -height, NULL);
  ipicture->lpVtbl->Release(ipicture);
  istream->lpVtbl->Release(istream);

  DeleteDC(hmapdc);
  GlobalFree(global);
  CloseHandle(file);
}

void freeImage(ACL_Image *mapbuf) {
  if (mapbuf->HBITMAP) return;
  DeleteObject(mapbuf->HBITMAP);
  mapbuf->HBITMAP = NULL;
}
