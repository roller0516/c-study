#include "BattleScene.h"
#include "PlayerShip.h"
#include "TileMapTool.h"
#include "EnemyManager.h"
#include "Image.h"
HRESULT BattleScene::Init()
{
	bin = new Image();
	bin->Init("Image/backGround_01.bmp", WINSIZE_X, WINSIZE_Y);

	enemyMgr = new EnemyManager();
	enemyMgr->Init();

	playerShip = new PlayerShip();
	playerShip->Init();

	tileMapTool = new TileMapTool();
	tileMapTool->Init();

	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(playerShip);
	SAFE_RELEASE(bin);
	SAFE_RELEASE(enemyMgr);
	SAFE_RELEASE(tileMapTool);
}

void BattleScene::Update()
{
	float currTime1 = TimerManager::GetSingleton()->GetCurrTime();
	
	if (enemyMgr)
	{
		enemyMgr->Update();
	}
	
	if (playerShip)
	{
		playerShip->Update();
	}
	
	CheckCollision();
	
	//TileMapTool Scene
	if (tileMapTool)
		tileMapTool->Update();
}

void BattleScene::Render(HDC hdc)
{
	if (bin)
	{
		bin->Render(hdc/*, -100, 100*/);
	}

	if (playerShip)
	{
		playerShip->Render(hdc);
	}

	if (enemyMgr)
	{
		enemyMgr->Render(hdc);
	}
	if (tileMapTool)
		tileMapTool->Render(hdc);
	// ÀÎ»ç
	TextOut(hdc, 20, 20, "MainGame ·»´õ Áß", strlen("MainGame ·»´õ Áß"));
	// ¸¶¿ì½º ÁÂÇ¥
	wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	TextOut(hdc, 200, 20, szText, strlen(szText));
}

void BattleScene::CheckCollision()
{
}
//	// Àû <-> ÅÊÅ© ¹Ì»çÀÏ 
//	float distance;
//	FPOINT enemyPos;
//	FPOINT missilePos;
//	float x, y;
//	int r1, r2;
//	Missile* missileArray = tank->GetMissile();

	//for (int i = 0; i < enemyCount; i++)
	//{
	//	if (enemy[i].GetIsAlive() == false)	continue;

	//	for (int j = 0; j < tank->GetMissileCount(); j++)
	//	{
	//		if (missileArray[j].GetIsFired() == false)	continue;

	//		enemyPos = enemy[i].GetPos();
	//		missilePos = missileArray[j].GetPos();

	//		x = enemyPos.x - missilePos.x;
	//		y = enemyPos.y - missilePos.y;

	//		distance = sqrtf(x * x + y * y);

	//		r1 = enemy[i].GetSize() / 2;
	//		r2 = missileArray[j].GetSize() / 2;

	//		if (distance <= r1 + r2)
	//		{
	//			enemy[i].SetIsAlive(false);
	//			missileArray[j].SetIsFired(false);
	//			break;
	//		}
	//	}
	//}

	// Àû <-> ÅÊÅ©

	// Àû ¹Ì»çÀÏ <-> ÅÊÅ©

	// Àû ¹Ì»çÀÏ <-> ÅÊÅ© ¹Ì»çÀÏ
