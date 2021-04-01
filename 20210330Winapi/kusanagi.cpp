#include "kusanagi.h"
#include "CommonFunction.h"

HRESULT Kusanagi::Init()
{
	img = new Image*[DIR::DIR_END];
	for (int i = 0; i < DIR::DIR_END; i++)
	{
		img[i] = new Image[STATE::STATE_END];
	}
	rectSize = 130;
	aniframe = 0;
	frame = 0;
	elapsedTime = 0;
	pos.x = 500;
	pos.y = WINSIZE_Y - 200;
	direction = 0;
	stateType = 0;
	FrameRun = false;
	HitBox = GetRectToCenter(pos.x, pos.y, rectSize, rectSize);

	if (FAILED(img[DIR::LEFT][STATE::IDLE].Init("Image/DuoLon/DuoLon_Idle.bmp", 728	, 130, 8, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/DuoLon/DuoLon_Idle.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	} // 왼쪽 숨쉬기
	else if (FAILED(img[DIR::LEFT][STATE::WALK].Init("Image/DuoLon/DuoLon_Walk_Front.bmp", 776, 130, 8, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/DuoLon/DuoLon_Walk_Front.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	} //왼쪽 걷기
	else if (FAILED(img[DIR::LEFT][STATE::WEAK_ATTACK_PUNCH].Init("Image/DuoLon/DuoLon_Weak_Punch.bmp", 476, 130, 4, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/DuoLon/DuoLon_Weak_Punch.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}// 왼쪽 약펀치
	else if (FAILED(img[DIR::LEFT][STATE::STRONG_ATTACK_PUNCH].Init("Image/DuoLon/DuoLon_Strong_Punch.bmp", 3104, 130, 16, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/DuoLon/DuoLon_Strong_Punch.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}// 왼쪽 강펀치
	else if (FAILED(img[DIR::LEFT][STATE::WEAK_ATTACK_KICK].Init("Image/DuoLon/DuoLon_Weak_Kick.bmp", 1302, 130, 7, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/DuoLon/DuoLon_Weak_Kick.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}// 왼쪽 약 발차기
	else if (FAILED(img[DIR::LEFT][STATE::STRONG_ATTACK_KICK].Init("Image/DuoLon/DuoLon_Strong_kick.bmp", 4004, 140, 22, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/DuoLon/DuoLon_Strong_kick.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}//왼쪽 강 발차기
	//--------------------------------------------------------RIGHT --------------------------------------------------------------------
	else if (FAILED(img[DIR::RIGHT][STATE::IDLE].Init("Image/kusanagi_Idle.bmp", 780, 111, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, "Image/DuoLon/kusanagi_Idle.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}//오른쪽 숨쉬기
	else if (FAILED(img[DIR::RIGHT][STATE::WALK].Init("Image/kusanagi_walk_R.bmp", 780, 111, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, "Image/kusanagi_Idle.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}//오른쪽 걷기
	else if (FAILED(img[DIR::RIGHT][STATE::WEAK_ATTACK_PUNCH].Init("Image/kusanagi_walk_R.bmp", 780, 111, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, "Image/kusanagi_Idle.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}// 오른쪽 약 펀치
	else if (FAILED(img[DIR::RIGHT][STATE::STRONG_ATTACK_PUNCH].Init("Image/kusanagi_walk_R.bmp", 780, 111, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, "Image/kusanagi_Idle.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}// 오른쪽 강 펀치
	else if (FAILED(img[DIR::RIGHT][STATE::WEAK_ATTACK_KICK].Init("Image/kusanagi_walk_R.bmp", 780, 111, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, "Image/kusanagi_Idle.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}// 오른쪽 약 발차기
	else if (FAILED(img[DIR::RIGHT][STATE::STRONG_ATTACK_KICK].Init("Image/kusanagi_walk_R.bmp", 780, 111, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, "Image/kusanagi_Idle.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}// 오른쪽 강 발차기
	return S_OK;
}

void Kusanagi::Release()
{
	for (int i = 0; i < DIR::DIR_END; i++)
	{
		for (int j = 0; j < STATE::STATE_END; j++)
		{
			img[i][j].Release();
		}
	}
}
	

void Kusanagi::Update()
{
	Move();
	Attack();
	elapsedTime++;
	if (elapsedTime >= 7)
		//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		frame++;
		if (frame >= aniframe)
		{
			frame = 0;
			FrameRun = false;
		}
		elapsedTime = 0;
		
	}
}

void Kusanagi::Render(HDC hdc)
{
	img[direction][stateType].Render(hdc, pos.x, pos.y, frame);
	Rectangle(hdc,HitBox.left,HitBox.right,HitBox.top,HitBox.bottom);
}

void Kusanagi::Move()
{
	if (KeyManager::Getsingleton()->IsStayKeyDown(VK_LEFT) && FrameRun == false)
	{
		aniframe = 8;
		direction = DIR::LEFT;
		stateType = STATE::WALK;
		pos.x -= 1;
	}
	else if (KeyManager::Getsingleton()->IsStayKeyDown(VK_RIGHT) && FrameRun == false)
	{
		aniframe = 8;
		direction = DIR::LEFT;
		stateType = STATE::WALK;
		pos.x += 1;
	}
	else if(FrameRun == false)
	{
		aniframe = 8;
		stateType = STATE::IDLE;
	}
}

void Kusanagi::Attack()
{
	
	if (KeyManager::Getsingleton()->IsOnceKeyDown('A') && FrameRun == false)
	{
		frame = 0;
		aniframe = 4;
		direction = DIR::LEFT;
		stateType = STATE::WEAK_ATTACK_PUNCH;
		FrameRun = true;
	}
	else if (KeyManager::Getsingleton()->IsOnceKeyDown('S') && FrameRun == false)
	{
		frame = 0;
		aniframe = 7;
		direction = DIR::LEFT;
		stateType = STATE::WEAK_ATTACK_KICK;
		FrameRun = true;
	}
	else if (KeyManager::Getsingleton()->IsOnceKeyDown('D') && FrameRun == false)
	{
		frame = 0;
		aniframe = 16;
		direction = DIR::LEFT;
		stateType = STATE::STRONG_ATTACK_PUNCH;
		FrameRun = true;
	}
	else if (KeyManager::Getsingleton()->IsOnceKeyDown('F') && FrameRun == false)
	{
		frame = 0;
		aniframe = 22;
		direction = DIR::LEFT;
		stateType = STATE::STRONG_ATTACK_KICK;
		FrameRun = true;
	}
}

void Kusanagi::Collision()
{

}
