#include "Bullet.h"

HRESULT Bullet::Init()
{
	pos = {-100, -100};
	speed = 15.0f;
	size = 20;
	shape = { 0, 0, 0, 0 };
	damage = 5000;
	angle = 0.0f;
	isFired = false;
	bulletType = TYPE::Normal;
	fireStep = 0;

	return S_OK;
}

void Bullet::Release()
{

}

void Bullet::Update()
{
	// 위치 이동
	if (isFired)
	{
		switch (bulletType)
		{
		case TYPE::Normal:
			MovingNormal();
			break;
		case TYPE::Skill_01:
			MovingSkill_01();
			break;
		case TYPE::End:

			break;
		}
		//나온 총알 하나가 윈도우 벗어나기 전까지는 발사 안댐, 최대 3개
		if (pos.x < 0 || pos.y < 0 || pos.x > WINSIZE_X || pos.y > WINSIZE_Y)
		{
			isFired = false;
			fireStep = 0;
		}
	}

	shape.left = pos.x - size / 2;
	shape.top = pos.y - size / 2;
	shape.right = pos.x + size / 2;
	shape.bottom = pos.y + size / 2;
	
	//Move();
}

void Bullet::Render(HDC hdc)
{
	Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
}

void Bullet::MovingNormal()
{
	pos.x += cosf(angle) * speed;				//결과값이 실수인데 정수값으로 받으니 오차가 생긴다.
	pos.y -= sinf(angle) * speed;
}

void Bullet::MovingSkill_01()
{
	if (fireStep == 0 && pos.y < 300.0f)
	{
		angle = fireIndex * 3.14f * 2.0f / 36.0f;
		fireStep++;
	}

	pos.x += cosf(angle) * speed;				//결과값이 실수인데 정수값으로 받으니 오차가 생긴다.
	pos.y -= sinf(angle) * speed;
}

//bool Bullet::isFire(bool fire)
//{
//	if (fire == true)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

//void Bullet::Move()
//{
//	pos.x += cosf(angle) * speed;
//	pos.y -= sinf(angle) * speed;
//}

//void Bullet::SetAngle(float Angle)
//{
//	this->angle = Angle;
//}