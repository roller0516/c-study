#pragma once
#include "GameNode.h"
class MainGame : public GameNode
{
private:
	bool isInited;
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	Image* backBuffer;
public:
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	HRESULT Init();
	void Release();
	void Update();
	void Render();
	MainGame();
	~MainGame();
};

