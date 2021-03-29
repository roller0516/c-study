//게임엔진 흉내내기 config.h	헤더끼리 묶어놓는다고 다 되는 것 아니다! 문법적으로 알고 있어야 한다.
#pragma once

#include <Windows.h>
#include <string>
#include <ctime>

using namespace std;

#define WINSIZE_X		1080
#define WINSIZE_Y		720

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

extern HWND g_hWnd;