#include "Missile.h"
#include "Enemy.h"
#include "CommonFunction.h"
HRESULT Missile::Init()
{
	pos = {-100, -100};
	firstpos = pos;
	moveSpeed = 5.0f;
	size = 10;
	shape = { 0, 0, 0, 0 };
	damage = 5000;
	angle = 0.0f;
	isFired = false;
	missileType = TYPE::Normal;
	angle2 = 0.0f;
	target = nullptr;
	targetOn = false;
	destAngle = 0.0f;
	delaytime = 0.0f;
    return S_OK;
}

void Missile::Release()
{
	//delete
}

void Missile::Update()
{
	// 위치 이동
	if (isFired)
	{
		switch (missileType)
		{
		case TYPE::Normal:

			Missile::MovingNormal();
			
				break;

		case TYPE:: Skill_01:

			Missile::MovingSkill_01();

				break;
		case TYPE ::Guided:

			Missile::MovingGuided();
				break;
		}
		if (pos.x < 0 || pos.y < 0 || pos.x > WINSIZE_X || pos.y > WINSIZE_Y)
		{
			isFired = false;
			fireStep = 0;
		}
	}
	if (target) 
	{
		delaytime += 0.1f;
		if (delaytime > 20.0f)
			delaytime = 0;
	}
		
	shape.left = pos.x - size / 2;
	shape.top = pos.y - size / 2;
	shape.right = pos.x + size / 2;
	shape.bottom = pos.y + size / 2;
}

void Missile::Render(HDC hdc)
{
	if (isFired) 
	{
		Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
	
	/*sprintf_s(szText, "angle2 : %f", angle2);
	TextOut(hdc, this->pos.x, this->pos.y, szText, strlen(szText));
	sprintf_s(szText, "angle : %f", angle);
	TextOut(hdc, this->pos.x, this->pos.y+20, szText, strlen(szText));
	sprintf_s(szText, "angle : %f", time);
	TextOut(hdc, this->pos.x, this->pos.y + 40, szText, strlen(szText));*/
}

void Missile::MovingNormal()
{
	pos.x += cosf(angle) * moveSpeed;
	pos.y -= sinf(angle) * moveSpeed;
}

void Missile::MovingSkill_01()
{
	if (fireStep == 0 && pos.y < 500.0f)
	{
		angle = fireIndex * 3.14f * 2.0f / 36.0f;
		targetOn = true;
		fireStep++;
	}
	if (target&& delaytime>10.0f)
	{
		destAngle = GetAngle(this->pos, target->GetPos());
		float ratio = (destAngle - angle) / 10.0f;

		if (-0.08f <= ratio && ratio <= 0.08f)
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

void Missile::MovingGuided()
{
	if (target)
	{
		destAngle = GetAngle(this->pos, target->GetPos());

		float ratio = (destAngle - angle) / 10.0f;

		if (-0.005f < ratio && ratio < 0.005f) 
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

