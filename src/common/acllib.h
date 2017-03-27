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
//    Ver 2014-07
//	For students' Lab at Zhejiang University
//	Created 	2008 by Gao Yuan
//	Modified 	2009 by Cui Liwei
//				    2010 by Lan Huidong
//	Revised		2012 by Li Rui
//  Modified  2014 by Weng Kai for MOOC
////////////////////////////////////////////////////////////////

/*
For Dev C++, these lib files need to be added into linker options. 
Be sure to change the leading folders as your installation.
"C:/Program Files/Dev-Cpp/MinGW32/lib/libwinmm.a"
"C:/Program Files/Dev-Cpp/MinGW32/lib/libmsimg32.a"
"C:/Program Files/Dev-Cpp/MinGW32/lib/libkernel32.a"
"C:/Program Files/Dev-Cpp/MinGW32/lib/libuser32.a"
"C:/Program Files/Dev-Cpp/MinGW32/lib/libgdi32.a"
"C:/Program Files/Dev-Cpp/MinGW32/lib/libole32.a"
"C:/Program Files/Dev-Cpp/MinGW32/lib/liboleaut32.a"
"C:/Program Files/Dev-Cpp/MinGW32/lib/libuuid.a" 
*/

#ifndef __ACLLIB_H__
#define __ACLLIB_H__

#include "platform.h"

#include "functionalities/paint.h"
#include "functionalities/events.h"
#include "functionalities/image.h"
#include "functionalities/window.h"
#include "functionalities/audio.h"

typedef enum
{
	TM_NO = 0x00,
	TM_COLOR = 0x01,
	TM_ALPHA = 0x02
} ACL_TransparentMode;


// 
int Setup();


//void putImageEx(ACL_Image *pImage,int dx,int dy,int dw,int dh, \
//	int sx,int sy,int sw,int sh);

//void setTransparentMode(ACL_TransparenetMode);
//void setTransparentColor(ACL_Color);
//void setTransparetnAlpha(int alpha);

#endif
