#include "BattleScene.h"
#include "Tank.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Missile.h"
#include "Image.h"
#include "Iori.h"
#include "PlayerShip.h"
#include "TilemapTool.h"

TILE_INFO BattleScene::tileInfo[TILE_X * TILE_Y];
HRESULT BattleScene::Init()
{
	bin = ImageManager::GetSingleton()->AddImage(
		"샘플타일", "Image/maptiles.bmp", 640, 288,
		TILE_X, TILE_Y);

	tank = new Tank();
	tank->Init();

	enemyMgr = new EnemyManager();
	enemyMgr->Init();

	playerShip = new PlayerShip();
	playerShip->Init();

	Load(1);

	/*for (int i = 0; i < TILE_Y; i++)
	{
		for (int j = 0; j < TILE_X; j++)
		{
			tileInfo[i * TILE_X + j].rcTile.left = TILESIZE * j;
			tileInfo[i * TILE_X + j].rcTile.top = TILESIZE * i;
			tileInfo[i * TILE_X + j].rcTile.right =
				tileInfo[i * TILE_X + j].rcTile.left + TILESIZE;
			tileInfo[i * TILE_X + j].rcTile.bottom =
				tileInfo[i * TILE_X + j].rcTile.top + TILESIZE;
		}
	}*/

	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(playerShip);
	SAFE_RELEASE(bin);
	SAFE_RELEASE(tank);
	SAFE_RELEASE(enemyMgr);
}

void BattleScene::Update()
{
	if (tank)
	{
		//tank->Update();
	}

	if (enemyMgr)
	{
		enemyMgr->Update();
	}

	if (playerShip)
	{
		playerShip->Update();
	}

	CheckCollision();
}

void BattleScene::Render(HDC hdc)
{
	/*if (tank)
	{
		tank->Render(hdc);
	}

	if (enemyMgr)
	{
		enemyMgr->Render(hdc);
	}

	if (playerShip)
	{
		playerShip->Render(hdc);
	}*/
	if (bin)
	{
		for (int i = 0; i < TILE_X * TILE_Y; i++)
		{
			bin->FrameRender(hdc,
				tileInfo[i].rcTile.left,
				tileInfo[i].rcTile.top,
				tileInfo[i].frameX,
				tileInfo[i].frameY);
		}
	}
	

}

void BattleScene::CheckCollision()
{
	// 적 <-> 탱크 미사일 
	float distance;
	FPOINT enemyPos;
	FPOINT missilePos;
	float x, y;
	int r1, r2;
	Missile* missileArray = tank->GetMissile();

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

	// 적 <-> 탱크

	// 적 미사일 <-> 탱크

	// 적 미사일 <-> 탱크 미사일
}

void BattleScene::Load(int stageNum)
{
	string fileName = "Save/saveMapData";  // 1.map";
	fileName += to_string(1) + ".map";

	DWORD readBytes;
	HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0,
		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	/*void**/
	if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
		&readBytes, NULL))
	{

	}
	else
	{
		MessageBox(g_hWnd, "저장파일 로드 실패", "실패", MB_OK);
	}

	CloseHandle(hFile);
}


