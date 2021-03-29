#pragma once
#include "GameNode.h"
#include "Tank.h"

class Bullet : public GameNode
{
public:
	enum TYPE { Normal, Skill_01, End };

private:
	FPOINT pos;
	float speed;
	int size;
	RECT shape;
	int damage;
	float angle;
	//bool isSet;
	bool isFired;
	TYPE bulletType;				// 0 : 일반, 1 : 스킬_01 ...
	int fireIndex;
	int fireStep;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void MovingNormal();
	void MovingSkill_01();

	//bool isFire(bool fire);
	//void Move();
	//void SetAngle(float Angle);
	inline void SetType(TYPE type) { this->bulletType = type; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline void SetIsFired(bool isFired) { this->isFired = isFired; }
	inline bool GetIsFired() { return this->isFired; }
	inline void SetAngle(float angle) { this->angle = angle; }
	inline void SetFireIndex(int fireIndex) { this->fireIndex = fireIndex; }
};

