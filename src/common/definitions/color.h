//
// Created by Colliot on 2016/9/6.
//

#ifndef ACLLIB_COLOR_H
#define ACLLIB_COLOR_H


#define BLACK            RGB(0, 0, 0)
#define RED                RGB(255, 0, 0)
#define GREEN            RGB(0, 255, 0)
#define BLUE            RGB(0, 0, 255)
#define CYAN            RGB(0, 255, 255)
#define MAGENTA            RGB(255, 0, 255)
#define YELLOW            RGB(255, 255, 0)
#define WHITE            RGB(255, 255, 255)

#define EMPTY                0xffffffff
#define DEFAULT                -1


typedef unsigned long DWORD;

typedef DWORD COLORREF;
typedef DWORD* LPCOLORREF;


typedef COLORREF ACL_Color;

#endif //ACLLIB_COLOR_H
