#pragma once
#include "GameNode.h"

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
	int Stage;
	int MonsterCount;
	int MaxMonsterCount;
	int enemyCount;
	int index;
	bool GameStart;

	Tank* tank;
	Enemy* enemy;
	Image* bin;
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

	inline int GetStage() { return Stage; }
	inline bool GetGameStart() { return GameStart; }
	inline int GetMonsterCount() { return MonsterCount; }
	inline int GetMaxMonsterCount() { return MaxMonsterCount; }
	inline void SetMonsterCount(int count) { MonsterCount = count; }
	inline void SetMaxMonsterCount(int count) { MaxMonsterCount = count; }
	inline void SetGameStart(bool end) { GameStart = end; }
	inline void SetStage(int stage) { this->Stage = stage; }

	void SetGame();
	MainGame();
	~MainGame();
};

