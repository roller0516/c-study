#pragma once
#include "GameNode.h"
class Enemy;
class Missile : public GameNode
{
public:
	enum TYPE {Normal, Skill_01, Guided ,End};

private:
	FPOINT pos;
	FPOINT firstpos;
	RECT shape;

	int size;
	int damage;
	int missileType;
	int fireIndex;
	int fireStep = 0;
	float delaytime;
	float angle;
	float angle2;
	bool isFired;
	bool targetOn;
	float moveSpeed;
	char szText[128] = "";
	/*GameNode* target;*/
	Enemy* target;
	float destAngle; // 차이각

public:
	HRESULT Init();		
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void MovingNormal();
	void MovingSkill_01();
	void MovingGuided(); // 유도탄


	//get set
	inline RECT GetRect() { return shape; }
	inline bool GetIsFired() { return this->isFired; }
	inline void SetIsFired(bool isFired) { this->isFired = isFired; }
	inline FPOINT GetPos() { return pos; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline int GetSize() { return size; }

	inline void SetTarget(Enemy* target) { this->target = target; }
	inline void SetFirstPos() { this->pos = this->firstpos; }
	inline void SetType(TYPE type) { this->missileType = type; }
	inline void SetAngle(float angle) { this->angle = angle; }
	inline void SetFireIndex(int fireIndex) { this->fireIndex = fireIndex; }
};

