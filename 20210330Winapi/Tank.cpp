#include "CommonFunction.h"
#include "Tank.h"
#include "Missile.h"
#include "Enemy.h"
HRESULT Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 30;
	size = 80;
	attackValue = 10;
	name = "��ũ";
	shape = GetRectToCenter(pos.x, pos.y, size, size);

	// ����
	barrelSize = 100;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = 3.14f / 4.0f;

	// �̻���
	missileCount = 300;
	missile = new Missile[missileCount];
	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Init();
	}

	//for (int i = 0; i < missileCount; i++)
	//{
	//	missile[i] = new Missile();
	//	missile[i]->Init();
	//}

	//missile = new Missile();
	//missile->Init();

	return S_OK;
}

void Tank::Release()
{
	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Release();
	}
	delete[] missile;

	//for (int i = 0; i < missileCount; i++)
	//{
	//	missile[i]->Release();
	//}
	//delete[] missile;

	//missile->Release();
	//delete missile;
}

void Tank::Update()
{
	// ���� ������ ���� ��ǥ ���
	barrelEnd.x = pos.x + cosf(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - (sinf(barrelAngle) * barrelSize);

	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Update();
	}
}

void Tank::Render(HDC hdc)
{
	// ����
	Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);

	// ����
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// �̻���
	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Render(hdc);
	}
}

void Tank::RotateBarrel(float angle)
{
	barrelAngle += angle;
}

void Tank::Move()
{
}

void Tank::Fire()
{
	// �̻��� �߻�
	// ���¸� ����
	for (int i = 0; i < missileCount; i++)
	{
		if (missile[i].GetIsFired() == false)
		{
			missile[i].SetType(Missile::TYPE::Normal);
			missile[i].SetPos(barrelEnd);
			missile[i].SetIsFired(true);
			missile[i].SetAngle(barrelAngle);
			break;
		}
	}
}

void Tank::Dead()
{

}

void Tank::FireSkill_01()
{
	int firedCount = 0;
	for (int i = 0; i < missileCount; i++)
	{
		if (firedCount < 36 && missile[i].GetIsFired() == false)
		{
			missile[i].SetType(Missile::TYPE::Skill_01);
			missile[i].SetPos(barrelEnd);
			missile[i].SetIsFired(true);
			missile[i].SetAngle(barrelAngle);
			missile[i].SetFireIndex(firedCount);
			firedCount++;
		}
	}
}
void Tank::FireSkill_02(Enemy* Enemy)
{
	for (int i = 0; i < missileCount; i++)
	{
		if (missile[i].GetIsFired() == false)
		{
			missile[i].SetType(Missile::TYPE::Guided);
			missile[i].SetPos(barrelEnd);
			missile[i].SetIsFired(true);
			missile[i].SetAngle(barrelAngle);
			missile[i].SetTarget(Enemy);
			break;
		}
		
	}
}



