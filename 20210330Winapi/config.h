// config.h

#pragma once

#include <Windows.h>
#include <string>
#include <ctime>
#include <cmath>
#include <bitset> // ������ ��ü�� ��Ʈ�� ǥ���Ǿ� �����Ҽ��ִ� �ڷᱸ��

#include "KeyManager.h"

using namespace std;

#define WINSIZE_X	1080
#define WINSIZE_Y	720

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

extern HWND g_hWnd;