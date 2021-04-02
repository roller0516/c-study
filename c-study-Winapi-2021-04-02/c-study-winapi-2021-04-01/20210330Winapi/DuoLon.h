#pragma once
#include "GameNode.h"
class Image;
class DuoLon :public GameNode
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
		HIT,
		WEAK_ATTACK_PUNCH,
		WEAK_ATTACK_KICK,
		STRONG_ATTACK_PUNCH,
		STRONG_ATTACK_KICK,
		CMOBO_ATTACK,
		STATE_END
	};
private:
	HBRUSH Brush, oldBrush;
	FPOINT pos;
	int elapsedTime;	// 100이 될 때마다 애니메이션 프레임을 1씩 증가
	int frame;			// 애니메이션 프레임 0 ~ 8
	int stateType;
	int direction;
	int maxFrame;
	int attackFrame;
	int rectSize;

	int inputKeyFrame;
	int MiddleFrame;
	int MaxKeyFrame;
	int count;

	int key[10];
	bool FrameRun;
	bool attackActiveOn;
	bool attack;
	bool comboAttack;
	bool comboAttack1;

	Image** img;

	RECT hitBox;
	RECT attackBox;
	RECT currentPos;

	typedef struct tagCollision
	{
		int x;
		int y;
		int width;
		int height;

		tagCollision()
		{
			x = 0;
			y = 0;
			width = 0;
			height = 0;
		}
	}CollisionSize ,* L_PCollisionSize;
	
public:
	CollisionSize* collisionsize;
	vector<int> inPutKey;
	vector<int> SavePutKey;
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	void Move();
	void Attack();
	void HitBoxCollision();
	void ComboAttack();
};

