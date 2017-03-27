//
// Created by Colliot on 2016/9/7.
//

#ifndef ACLLIB_MACROS_H
#define ACLLIB_MACROS_H

/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
////////////////////////////////////////////////////////////////
//  ACLLib - Advanced C Lab Library
//    Ver. 2014-07
//	For Students' Lab at Zhejiang University
//	Created 	2008 by Gao Yuan
//	Modified 	2009 by Cui Liwei
//				    2010 by Lan Huidong
//	Revised		2012 by Li Rui
//  Modified  2014 by Weng Kai for MOOC
////////////////////////////////////////////////////////////////
#define ACL__WIN32_
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#define CINTERFACE

#ifdef _UNICODE
#undef _UNICODE
#endif
#ifdef UNICODE
#undef UNICODE
#endif

#include "../common/acllib.h"

#include <windows.h>
#include <olectl.h>
#include <stdio.h>

// f
int Setup(void);

extern const char g_wndClassName[];
extern const char g_libName[];

extern HINSTANCE g_hInstance;

extern HWND g_hWnd;
extern HDC g_hmemdc;
extern HBITMAP g_HBITMAP;

extern int g_wndHeight;
extern int g_wndWidth;

extern HPEN g_pen;
extern ACL_Color g_penColor;
extern int g_penWidth;
extern int g_penStyle;

extern HBRUSH g_brush;
extern ACL_Color g_brushColor;
extern int g_brushStyle;

extern HFONT g_font;
extern char g_fontName[256];
extern int g_textSize;
extern ACL_Color g_textColor;
extern ACL_Color g_textBkColor;

extern int g_caretHeight;
extern int g_caretWidth;
extern int g_caretX;
extern int g_caretY;

extern int g_soundID;

extern KeyboardEventCallback g_keyboard;
extern MouseEventCallback g_mouse;
extern TimerEventCallback g_timer;
extern CharEventCallback g_char;


#ifdef _MSC_VER
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"msimg32.lib")
#endif

#ifdef _DEBUG
#define ACL_ASSERT(_Expression,errStr) (void)( (!!(_Expression)) || (acl_error(errStr),0) )
#else
#define ACL_ASSERT(flag, errStr) ((void)0)
#endif

#define ACL_ASSERT_HWND ACL_ASSERT(g_hWnd!=0, \
    "You should call function \"initWindow(...)\" befor use function \"" __FUNCTION__ "\"" )
#define ACL_ASSERT_BEGIN_PAINT ACL_ASSERT(g_hmemdc!=0, \
    "You should call function \"beginPaint()\" befor use function \"" __FUNCTION__ "\"" )

#endif //ACLLIB_MACROS_H
