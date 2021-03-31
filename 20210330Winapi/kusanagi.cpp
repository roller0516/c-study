#include "kusanagi.h"
#include "Image.h"

HRESULT Kusanagi::Init()
{
	frame = 0;
	elapsedTime = 0;
	StateType = WALKSTATE::END;
	pos.x = 500;
	pos.y = WINSIZE_Y - 200;

	img = new Image();

	if (FAILED(img->Init("Image/kusanagi_Idle.bmp", 780, 111)))
	{
		MessageBox(g_hWnd, "Image/kusanagi_Idle.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void Kusanagi::Release()
{
	if (img)
	{
		img->Release();
		delete img;
		img = nullptr;
	}
}

void Kusanagi::Update()
{
	elapsedTime++;
	if (elapsedTime >= 10)
		//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		frame++;
		if (frame >= 6)
		{
			frame = 0;
		}
		elapsedTime = 0;
		
	}
	if (KeyManager::Getsingleton()->IsStayKeyDown(VK_RIGHT))
	{
		pos.x += 10;
		StateType = WALKSTATE::RIGHT;
	}
	else if (KeyManager::Getsingleton()->IsStayKeyDown(VK_LEFT))
	{
		pos.x -= 10;
		StateType = WALKSTATE::LEFT;
	}
	else
		StateType = WALKSTATE::IDLE;
		
}

void Kusanagi::Render(HDC hdc)
{
	if (img)
	{
		switch (StateType)
		{
		case WALKSTATE::IDLE:
			img->Init("Image/kusanagi_Idle.bmp", 780, 111);
			img->Render(hdc, pos.x, pos.y, frame, 10);
			break;
		case WALKSTATE::LEFT:
			img->Init("Image/kusanagi_walk_L.bmp", 500, 114);
			img->Render(hdc, pos.x, pos.y, frame, 6);
			break;
		case WALKSTATE::RIGHT:
			img->Init("Image/kusanagi_walk_R.bmp", 500, 114);
			img->Render(hdc, pos.x, pos.y, frame, 6);
			break;
		}
	}
}
