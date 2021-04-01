#pragma once
#include "GameNode.h"
class Image;
class Kusanagi :public GameNode
{
public:
	enum DIR
	{
		LEFT,
		RIGHT,
		DIR_END
	};
	enum STATE
	{
		IDLE,
		WALK,
		WEAK_ATTACK_PUNCH,
		WEAK_ATTACK_KICK,
		STRONG_ATTACK_PUNCH,
		STRONG_ATTACK_KICK,
		STATE_END
	};
private:
	FPOINT pos;
	int elapsedTime;	// 100이 될 때마다 애니메이션 프레임을 1씩 증가
	int frame;			// 애니메이션 프레임 0 ~ 8
	int stateType;
	int direction;
	int aniframe;
	Image** img;
	bool FrameRun;
	RECT HitBox;
	RECT AttackBox;
	int rectSize;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void Move();
	void Attack();
	void Collision();
};

