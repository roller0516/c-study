#pragma once
#include "GameNode.h"

//TODO : ��ĳ����, �ٿ�ĳ���� ����
class Tank;
class Enemy : public GameNode
{
private:
	FPOINT pos;
	int size;
	string name;
	RECT shape;
	float moveSpeed;
	float angle;
	bool isAlive;
	int index;
	/*GameNode* target;*/
	Tank* target;
public :
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	void Move();

	//get set
	inline FPOINT GetPos() { return this->pos; }
	inline int GetSize() { return size; }
	inline void SetisAlive(bool alive) { this->isAlive = alive; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline void SetTarget(Tank* tank) { this->target = tank; }
	inline bool GetIsAlive() { return this->isAlive; }
};

