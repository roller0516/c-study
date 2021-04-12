#include "MainGame.h"
#include "Image.h"
#include "EnemyManager.h"
HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	// ���ΰ����� �ʱ�ȭ �Լ�
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	ImageManager::GetSingleton()->AddImage("Enemy", "Image/ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Missile", "Image/����.bmp", 20, 20, true, RGB(255, 0, 255));
	// ����� �̹���
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	bin = new Image();
	bin->Init("Image/background.bmp", WINSIZE_X, WINSIZE_Y);

	// ������ ��ġ�� ����

	enemyManager = new EnemyManager();
	enemyManager->Init();
	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();

	backBuffer->Release();
	delete backBuffer;
	backBuffer = nullptr;

	bin->Release();
	delete bin;
	bin = nullptr;


	enemyManager->Release();
	delete enemyManager;
	enemyManager = nullptr;

	KillTimer(g_hWnd, 0);
}

void MainGame::Update()
{
	//CheckCollision();
	enemyManager->Update();
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackDC = backBuffer->GetMemDC();

	if (bin)
	{
		bin->Render(hBackDC/*, -100, 100*/);
	}
	enemyManager->Render(hBackDC);
	// �λ�
	TextOut(hBackDC, 20, 20, "MainGame ���� ��", strlen("MainGame ���� ��"));
	// ���콺 ��ǥ
	wsprintf(szText, "X : %d, Y : %d", ptMouse.x, ptMouse.y);
	TextOut(hBackDC, 200, 20, szText, strlen(szText));


	backBuffer->Render(hdc);
}

//void MainGame::CheckCollision()
//{
//	// �� <-> ��ũ �̻��� 
//	float distance;
//	FPOINT enemyPos;
//	FPOINT missilePos;
//	float x, y;
//	int r1, r2;
//
//	for (int i = 0; i < enemyCount; i++)
//	{
//		if (enemy[i].GetIsAlive() == false)	continue;
//
//		for (int j = 0; j < tank->GetMissileCount(); j++)
//		{
//			if (missileArray[j].GetIsFired() == false)	continue;
//
//			enemyPos = enemy[i].GetPos();
//			missilePos = missileArray[j].GetPos();
//
//			x = enemyPos.x - missilePos.x;
//			y = enemyPos.y - missilePos.y;
//
//			distance = sqrtf(x * x + y * y);
//
//			r1 = enemy[i].GetSize() / 2;
//			r2 = missileArray[j].GetSize() / 2;
//
//			if (distance <= r1 + r2)
//			{
//				enemy[i].SetIsAlive(false);
//				missileArray[j].SetIsFired(false);
//				break;
//			}
//		}
//	}
//
//	// �� <-> ��ũ
//
//	// �� �̻��� <-> ��ũ
//
//	// �� �̻��� <-> ��ũ �̻���
//}

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

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
