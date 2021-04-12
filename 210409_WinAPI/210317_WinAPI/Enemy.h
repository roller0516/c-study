#pragma once
#include "GameNode.h"

// TODO : 업캐스팅, 다운캐스팅 설명
class Image;
class MissileManager;
class Enemy : public GameNode
{
private:
	MissileManager* missileManager;

	Image* image;

	FPOINT pos;
	RECT shape;
	string name;
	float moveSpeed;
	float angle;
	bool isAlive;
	bool isAttack;
	int currFrameX;
	int size;
	int dir;
	int hp;
	//GameNode* target;
	//Tank* target;
	int elapsedTime;
	int elapsedTime2;
	int attackTime;
	int FireCount;
public:
	HRESULT Init(int width, int height);
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void Move();
	void HorizonMove();
	void Pattern1();
	// get, set
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline FPOINT GetPos() { return this->pos; }
	inline int GetSize() { return this->size; }
	inline bool GetIsAlive() { return this->isAlive; }
};

