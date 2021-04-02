// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <ctime>
#include <cmath>
#include <bitset> // 데이터 자체가 비트로 표현되어 저장할수있는 자료구조
#include <vector>

#include "KeyManager.h"
#include "Image.h"

using namespace std;

#define WINSIZE_X	1080
#define WINSIZE_Y	720

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;