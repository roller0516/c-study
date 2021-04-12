#include "Missile.h"
#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"

HRESULT Missile::Init(/*Enemy* owner*/)
{

	//this->owner = owner;

	//pos = this->owner->GetPos();
	pos = { };
	moveSpeed = 5.0f;
	size = 50;
	shape = { 0, 0, 0, 0 };
	damage = 5000;
	angle = 0.0f;
	isFired = false;
	missileType = TYPE::Normal;
	fireStep = 0;
	target = nullptr;
	destAngle = 0.0f;
	interval = 0;
	// 이미지
	img = ImageManager::GetSingleton()->FindImage("Missile");
	if (img == nullptr) 
	{
		MessageBox(g_hWnd, " Missile에 해당하는 이미지가 없습니다","이미지 경고" ,MB_OK);
		return E_FAIL;
	}

    return S_OK;
}

void Missile::Release()
{
	ImageManager::GetSingleton()->DeleteImage("Missile");
}

void Missile::Update()
{

	// 위치 이동
	if (isFired)
	{
		switch (missileType)
		{
		case TYPE::Normal:
			MovingNormal();
			break;
		case TYPE::Skill_01:
			MovingSkill_01();
			break;
		case TYPE::FollowTarget:
			MovingFollowTarget();
			break;
		case TYPE::StarMoving:
			MovigStar();
			break;
		}
		if (pos.x < 0 || pos.y < 0 || pos.x > WINSIZE_X || pos.y > WINSIZE_Y)
		{
			isFired = false;
			isDraw = false;
			fireStep = 0;
			timer = 0;
		}
	}
	
	
	shape.left = pos.x - size / 2;
	shape.top = pos.y - size / 2;
	shape.right = pos.x + size / 2;
	shape.bottom = pos.y + size / 2;
}

void Missile::Render(HDC hdc)
{
	if(isDraw)
		img->Render(hdc, pos.x - (size / 2), pos.y - (size / 2));
}

void Missile::MovingNormal()
{
	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}

void Missile::MovingSkill_01()
{
	if (fireStep == 0 && pos.y < WINSIZE_Y)
	{
		interval += 12;
		if (interval >= 360)
			interval = 0;
		angle = fireIndex * 3.14f * 8 / interval;
		fireStep++;
	}

	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}

void Missile::MovingFollowTarget()
{
	if (target)
	{
		destAngle = GetAngle(pos, target->GetPos());
		float ratio = (destAngle - angle) / 50.0f;

		if (-0.01f < ratio && ratio < 0.01f)
		{
			angle = destAngle;
		}
		else
		{
			angle += ratio;
		}
	}

	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}

void Missile::MovigStar()
{
	FPOINT targetPos;
	targetPos.x = 100;
	targetPos.y = 100;
	float x, y;

	timer++;
	if (timer <= 100) 
	{
		if (fireStep == 0 && pos.y < WINSIZE_Y)
		{
			angle = fireIndex * 3.14f * 2.0f / 90.0f;
			fireStep++;
			
		}
		pos.x += cosf(angle) * moveSpeed;
		pos.y -= sinf(angle) * moveSpeed;
	}
	/*else 
	{
		x = targetPos.x - this->pos.x;
		y = targetPos.y - this->pos.y;
		angle = atan2(-y, x);
		pos.x += cosf(angle) * moveSpeed;
		pos.y += sinf(angle) * moveSpeed;
	}*/
}

void Missile::SetIsFired(bool isFired)
{
	this->isFired = isFired;
	//pos.x = owner->GetPos().x;
	//pos.y = owner->GetPos().y;
}

