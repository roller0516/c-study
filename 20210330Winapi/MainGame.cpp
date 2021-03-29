#include "MainGame.h"
#include "Tank.h"
#include "Enemy.h"
#include "Missile.h"
HRESULT MainGame::Init()
{
	// 메인게임의 초기화 함수
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	index = 0;
	tank = new Tank();
	tank->Init();
	FPOINT randPos;
	srand(time(NULL));
	enemyCount = 36;
	enemy = new Enemy[enemyCount]; // 동적할당
	for (int i = 0; i < enemyCount; i++)
	{
		enemy[i].Init();
		enemy[i].SetTarget(tank);

		randPos.x = rand() % WINSIZE_X;
		randPos.y = rand() % 200;
		enemy[i].SetPos(randPos);
	}

	Stage = 1;
	MaxMonsterCount = 1;
	MonsterCount = MaxMonsterCount;
	isInited = true;
	GameStart = true;
	return S_OK;
}

void MainGame::Release()
{
	for (int i = 0; i < enemyCount; i++)
		enemy[i].Release();
	delete[] enemy;
	enemy = nullptr;

	tank->Release();
	delete tank;
	tank = nullptr;

	KillTimer(g_hWnd, 0);
}

void MainGame::Update()
{
	if (tank) 
	{
		tank->Update();
		
	}
	if (enemy) 
	{

		for (int i = 0; i < enemyCount; i++)
		{
			enemy[i].Update();
		}
	}
	SetGame();
	CheckCollision();
	//EnemyTarget();
	InvalidateRect(g_hWnd, NULL, true);
}

void MainGame::Render(HDC hdc)
{
	// 인사
	TextOut(hdc, 20, 20, "MainGame 렌더 중", strlen("MainGame 렌더 중"));
	// 마우스 좌표
	wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	TextOut(hdc, 200, 20, szText, strlen(szText));
	wsprintf(szText, "현재스테이지 : %d", Stage);
	TextOut(hdc, 500, 20, szText, strlen(szText));
	wsprintf(szText, "MonsterCount : %d", MonsterCount);
	TextOut(hdc, 700,20, szText, strlen(szText));
	if (enemy) 
	{
		for (int i = 0; i < enemyCount; i++)
			enemy[i].Render(hdc);
	}
		
	if (tank) 
	{
		tank->Render(hdc);
	}
}

void MainGame::CheckCollision()
{
	float  distance;
	FPOINT enemyPos;
	FPOINT missilePos;
	float x,y;
	int r1,r2;
	Missile* missileArray = tank->GetMissile();
	//적 <-> 탱크 미사일
	for (int i = 0; i < enemyCount; i++) 
	{
		if (enemy[i].GetIsAlive() == false) continue;// 죽었음
		for (int j = 0; j < tank->GetMissileCount(); j++) 
		{
			if (missileArray[j].GetIsFired() == false) continue;

			enemyPos = enemy[i].GetPos();
			missilePos = missileArray[j].GetPos();

			x = enemyPos.x - missilePos.x;
			y = enemyPos.y - missilePos.y;

			distance = sqrtf(x * x + y * y);

			r1 = enemy[i].GetSize()/2;
			r2 = missileArray[j].GetSize()/2;

			if (distance <= r1 + r2) //충돌 했음
			{
				enemy[i].SetisAlive(false);
				missileArray[j].SetIsFired(false);
				break;
			} 
		}
	}
	//적 <->탱크
	//적 미사일 <-> 탱크
	//적 미사일 <-> 탱크 미사일
}

void MainGame::EnemyTarget()
{
	Missile* missile = tank->GetMissile();
	float distance;
	float targetDistance =200.0f;
	FPOINT enemyPos;
	FPOINT missilePos;
	float x, y;
	int targetIndex = 0;
	int closeDistIndex;

	for (int i = 0; i < enemyCount; i++) 
	{
		if (enemy[i].GetIsAlive() == false) continue;
		for (int j = 0; j < tank->GetMissileCount(); j++)
		{
			if (missile[j].GetIsFired() == false) continue;

			//거리를 계산
			enemyPos = enemy[i].GetPos();
			missilePos = missile[j].GetPos();

			x = enemyPos.x - missilePos.x;
			y = enemyPos.y - missilePos.y;

			distance = sqrt(x * x + y * y);

			if (targetDistance >= distance)
			{
				targetIndex = i;
				targetDistance = distance;
			}
		}
		targetDistance = 200;
	}
	
}

void MainGame::SetMissileTarget()
{
	Missile* missile = tank->GetMissile();

	for (int i = 0; i < enemyCount; i++) 
	{
		for (int j = 0; j < tank->GetMissileCount(); j++)
		{
			if (i == j && enemy[i].GetIsAlive() == true)
				missile[j].SetTarget(&enemy[i]);
		}
	}
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		if (isInited)
		{
			this->Update();
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'f': case 'F':
			if (tank) 
			{
				tank->FireSkill_01();
				SetMissileTarget();
			}
			break;
		case'q':case'Q':
			if (tank) 
			{
				if (enemyCount > index)
				{
					tank->FireSkill_02(&enemy[index]);
					index++;
				}
			}
			break;
		case VK_LEFT:
			if(tank)
			tank->RotateBarrel(0.07f);
			break;
		case VK_RIGHT:
			if(tank)
			tank->RotateBarrel(-0.07f);
			break;
		case VK_SPACE:
			// 미사일 발사 - tank
			if(tank)
			tank->Fire();
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);

		if (isInited)
		{
			this->Render(hdc);
		}

		EndPaint(g_hWnd, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void MainGame::SetGame()
{
	/*if (MonsterCount == 0)
	{
		for (int i = 0; i < Stage; i++) 
			enemy[i].move = true;
			
		this->Stage++;
		this->MaxMonsterCount++;
		this->MonsterCount = this->MaxMonsterCount;
	}
	for (int i = 0; i < Stage; i++) 
	{
		if (Enemy[i].GetDestroy() == true) 
		{
			Enemy[i].move = false;
			Enemy[i].SetDestroy(false);
			this->MonsterCount--;
		}	
	}*/
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
