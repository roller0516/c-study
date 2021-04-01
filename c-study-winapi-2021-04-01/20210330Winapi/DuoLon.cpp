#include "DuoLon.h"
#include "CommonFunction.h"

HRESULT DuoLon::Init()
{
	img = new Image*[DIR::DIR_END];
	for (int i = 0; i < DIR::DIR_END; i++)
	{
		img[i] = new Image[STATE::STATE_END];
	}

	rectSize = 100;
	maxFrame = 0;
	attackFrame = 100;
	frame = 0;
	elapsedTime = 0;
	pos.x = 500;
	pos.y = WINSIZE_Y - 200;
	direction = 0;
	stateType = 0;
	FrameRun = false;
	hitBox = GetRectToCenter(pos.x+ 50, pos.y+50, rectSize, rectSize+ 60);
	currentPos = { -100,-100,-100,-100 };
	attackBox = currentPos;
	Brush = (HBRUSH)GetStockObject(NULL_BRUSH);
	attackActiveOn = false;
	attack = false;
	collisionsize = new CollisionSize;

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
	else if (FAILED(img[DIR::LEFT][STATE::HIT].Init("Image/kusanagi_walk_R.bmp", 780, 111, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, "Image/kusanagi_Idle.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}// 왼쪽 히트
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
	else if (FAILED(img[DIR::LEFT][STATE::STRONG_ATTACK_KICK].Init("Image/DuoLon/DuoLon_Strong_kick.bmp", 3972, 130, 22, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/DuoLon/DuoLon_Strong_kick.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}//왼쪽 강 발차기
	else if (FAILED(img[DIR::LEFT][STATE::CMOBO_ATTACK].Init("Image/DuoLon/DuoLon_Strong_kick.bmp", 3972, 140, 22, 1, true, RGB(255, 255, 255))))
	{
		MessageBox(g_hWnd, "Image/DuoLon/DuoLon_Strong_kick.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}//왼쪽 콤보 어택
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
	else if (FAILED(img[DIR::RIGHT][STATE::HIT].Init("Image/kusanagi_walk_R.bmp", 780, 111, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, "Image/kusanagi_Idle.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}// 오른쪽 히트
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
	else if (FAILED(img[DIR::RIGHT][STATE::CMOBO_ATTACK].Init("Image/kusanagi_walk_R.bmp", 780, 111, 10, 1, true, RGB(255, 0, 255))))
	{
		MessageBox(g_hWnd, "Image/kusanagi_Idle.bmp 로드 실패", "경고", MB_OK);
		return E_FAIL;
	}// 오른쪽 콤보 어택
	return S_OK;
}

void DuoLon::Release()
{
	for (int i = 0; i < DIR::DIR_END; i++)
	{
		for (int j = 0; j < STATE::STATE_END; j++)
		{
			img[i][j].Release();
		}
	}
	delete collisionsize;
	DeleteObject(Brush);
}
	

void DuoLon::Update()
{
	Move();
	Attack();
	elapsedTime++;
	if (elapsedTime >= 5)
		//if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		frame++;
		
		if(frame > attackFrame&& frame <= attackFrame +2 && attack == true)
		{
			attackActiveOn = true;
		}
		else 
		{
			attackActiveOn = false;
		}
		if (frame >= maxFrame)
		{
			frame = 0;
			FrameRun = false;
			attack = false;
		}
		elapsedTime = 0;
	}

	

	HitBoxCollision();
}

void DuoLon::Render(HDC hdc)
{
	img[direction][stateType].Render(hdc, pos.x , pos.y , frame);
	oldBrush = (HBRUSH)SelectObject(hdc, Brush);
	Rectangle(hdc, attackBox.left, attackBox.top, attackBox.right, attackBox.bottom);
	oldBrush = (HBRUSH)SelectObject(hdc, Brush);
	Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
	SelectObject(hdc, oldBrush);
}

void DuoLon::Move()
{
	if (KeyManager::Getsingleton()->IsStayKeyDown(VK_LEFT) && FrameRun == false)
	{
		maxFrame = 8;
		direction = DIR::LEFT;
		stateType = STATE::WALK;
		pos.x -= 1;
	}
	else if (KeyManager::Getsingleton()->IsStayKeyDown(VK_RIGHT) && FrameRun == false)
	{
		maxFrame = 8;
		direction = DIR::LEFT;
		stateType = STATE::WALK;
		pos.x += 1;
	}
	else if(FrameRun == false)
	{
		maxFrame = 8;
		stateType = STATE::IDLE;
	}
}

void DuoLon::Attack()
{
	if (KeyManager::Getsingleton()->IsOnceKeyDown('A') && FrameRun == false)
	{
		collisionsize->x = pos.x + 100;
		collisionsize->y = pos.y + 50;
		collisionsize->width = rectSize - 50;
		collisionsize->height = rectSize + 60;

		frame = 0;
		maxFrame = 4;
		attackFrame = 2;
		direction = DIR::LEFT;
		stateType = STATE::WEAK_ATTACK_PUNCH;
		attack = true;
		FrameRun = true;
	}
	else if (KeyManager::Getsingleton()->IsOnceKeyDown('S') && FrameRun == false)
	{
		collisionsize->x = pos.x + 120;
		collisionsize->y = pos.y + 50;
		collisionsize->width = rectSize - 10;
		collisionsize->height = rectSize + 60;

		frame = 0;
		attackFrame = 4;
		maxFrame = 7;
		direction = DIR::LEFT;
		stateType = STATE::WEAK_ATTACK_KICK;
		attack = true;
		FrameRun = true;
	}
	else if (KeyManager::Getsingleton()->IsOnceKeyDown('D') && FrameRun == false)
	{
		collisionsize->x = pos.x + 150;
		collisionsize->y = pos.y + 50;
		collisionsize->width = rectSize - 10;
		collisionsize->height = rectSize + 60;

		frame = 0;
		attackFrame = 8;
		maxFrame = 16;
		direction = DIR::LEFT;
		stateType = STATE::STRONG_ATTACK_PUNCH;
		attack = true;
		FrameRun = true;
	}
	else if (KeyManager::Getsingleton()->IsOnceKeyDown('F') && FrameRun == false)
	{
		collisionsize->x = pos.x + 170;
		collisionsize->y = pos.y + 50;
		collisionsize->width = rectSize - 10;
		collisionsize->height = rectSize + 60;

		frame = 0;
		attackFrame = 10;
		maxFrame = 22;
		direction = DIR::LEFT;
		stateType = STATE::STRONG_ATTACK_KICK;
		attack = true;
		FrameRun = true;
	}
	if (attackActiveOn == true)
		attackBox = GetRectToCenter(collisionsize->x, collisionsize->y, collisionsize->width, collisionsize->height);
	else
		attackBox = currentPos;
	
}

void DuoLon::HitBoxCollision()
{
	hitBox.left = (pos.x + 50) - rectSize / 2;
	hitBox.top = (pos.y + 50) - (rectSize + 60) / 2;
	hitBox.right = (pos.x + 50) + rectSize / 2;
	hitBox.bottom = (pos.y + 50) + (rectSize + 60) / 2;
}

