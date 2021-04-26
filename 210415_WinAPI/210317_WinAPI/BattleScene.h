#pragma once
#include "GameNode.h"

class TileMapTool;
class PlayerShip;
class Iori;
class Tank;
class Enemy;
class EnemyManager;
class Image;
class BattleScene :public GameNode
{
private :
	POINT ptMouse{ 0, 0 };
	char szText[128] = "";

	Image* bin;

	Tank* tank;

	EnemyManager* enemyMgr;

	PlayerShip* playerShip;

	TileMapTool* tileMapTool;
public:
	virtual	HRESULT Init();		// 오버라이딩 : 다형성
	virtual	void Release();
	virtual	void Update();
	virtual	void Render(HDC hdc);

	void CheckCollision();
	void SetMousePoint(int x ,int y) {
		this->ptMouse.x = x;
		this->ptMouse.y = y;
	}
};

