//
// Created by Colliot on 2016/9/6.
//

#ifndef PROJECT_PLATFORM_H
#define PROJECT_PLATFORM_H

#ifndef WIN32
#ifndef ACL__WIN32_
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
#define RGB(r,g,b)      ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

//typedef void *PVOID;
//typedef PVOID HANDLE;
//typedef HANDLE HBITMAP;
//
//typedef long LONG;
//
//typedef struct tagPOINT {
//  LONG x;
//  LONG y;
//} POINT, *PPOINT;
#else
#include <windows.h>
#endif
//typedef struct tagPoint POINT, *PPOINT;
#else
#include <windows.h>
#endif
#endif //PROJECT_PLATFORM_H
