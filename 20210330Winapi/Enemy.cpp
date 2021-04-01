#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "MainGame.h"
HRESULT Enemy::Init()
{
	pos.x = 0;
	pos.y = 0;
	size = 20;
	name = "NormalEnemy";
	shape = {0,0,0,0};
	moveSpeed = 1.0f;
	isAlive = true;
	target = nullptr;

	index = 0;
	return S_OK;
}

void Enemy::Release()
{

}

void Enemy::Update()
{
	if(isAlive)
		Move();
}

void Enemy::Render(HDC hdc)
{
	if(isAlive)
		RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
}

void Enemy::Move()
{
	if (target) 
	{
		FPOINT targetpos =	target->Getpos();

		float x = targetpos.x - pos.x;
		float y = targetpos.y - pos.y;

		angle = atan2f(y , x);

		pos.x += cosf(angle) * moveSpeed;
		pos.y += sinf(angle) * moveSpeed;
	}
}



