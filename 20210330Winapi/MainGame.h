#pragma once
#include "GameNode.h"
class Kusanagi;
class Iori;
class Tank;
class Enemy;
class Image;
class MainGame : public GameNode
{
private:
	bool isInited;

	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	POINT ptMouse{ 0, 0 };
	char szText[128] = "";
	int enemyCount;
	int index;

	Tank* tank;
	Enemy* enemy;
	Image* bin;
	Image* backBuffer;
	Iori* iori;
	Kusanagi* kusanagi;
	//EnemyTank* Enemy;

public:
	HRESULT Init();		// 오버라이딩 : 다형성
	void Release();
	void Update();
	void Render(HDC hdc);

	void CheckCollision();
	void EnemyTarget();
	void SetMissileTarget();
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	void SetGame();
	MainGame();
	~MainGame();
};

