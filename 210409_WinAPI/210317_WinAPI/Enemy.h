#pragma once
#include "GameNode.h"

// TODO : 업캐스팅, 다운캐스팅 설명
class Image;
class Tank;
class Enemy : public GameNode
{
private:
	Image* image;
	int currFrameX;

	FPOINT pos;
	RECT shape;
	string name;
	float moveSpeed;
	float angle;
	bool isAlive;
	int size;
	int dir;

	//GameNode* target;
	Tank* target;

	int elapsedTime;

public:
	HRESULT Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void Move();
	void HorizonMove();

	// get, set
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline void SetTarget(Tank* target) { this->target = target; }
	inline int GetSize() { return this->size; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }
};

