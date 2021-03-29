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
	// ��ġ �̵�
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
		//���� �Ѿ� �ϳ��� ������ ����� �������� �߻� �ȴ�, �ִ� 3��
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
	pos.x += cosf(angle) * speed;				//������� �Ǽ��ε� ���������� ������ ������ �����.
	pos.y -= sinf(angle) * speed;
}

void Bullet::MovingSkill_01()
{
	if (fireStep == 0 && pos.y < 300.0f)
	{
		angle = fireIndex * 3.14f * 2.0f / 36.0f;
		fireStep++;
	}

	pos.x += cosf(angle) * speed;				//������� �Ǽ��ε� ���������� ������ ������ �����.
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