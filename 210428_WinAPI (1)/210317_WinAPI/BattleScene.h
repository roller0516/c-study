#pragma once
#include "GameNode.h"



// ���� MainGame Ŭ������ ������ �̵�
class TilemapTool;
class PlayerShip;
class Tank;
class EnemyManager;
class Image;
class BattleScene : public GameNode
{
private:
	Image* bin;
	Tank* tank;
	EnemyManager* enemyMgr;
	PlayerShip* playerShip;
	TilemapTool* tileMapTool;
public:
	static TILE_INFO tileInfo[TILE_X * TILE_Y];
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void CheckCollision();
	void Load(int stageNum);
	virtual ~BattleScene() {};
};

