#pragma once
#include "GameNode.h"
//#include "MainGame.h"
//#include "Missile.h"

/*
	is-a 관계		탱크는 게임노드이다.
	has-a 관계		탱크는 미사일을 가지고 있다.
					적은 탱크의 좌표를 가지고있다.
*/
class Enemy;
class Missile;		// 전방선언
class Tank : public GameNode
{
private: // 비밀
	// 속성 : 멤버변수
	FPOINT pos;

	int size;
	float attackValue;
	string name;
	RECT shape;

	// 포신
	// 포신의 시작점, 끝점
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;	

	// 미사일
	int missileCount;
	Missile* missile;		// 2
	
//* -> 주소! 동적배열할때는 무조건 
	//[]배열  * 같은거임 
public:
	HRESULT Init();
	void Release();		
	void Update();		
	void Render(HDC hdc);
	void RotateBarrel(float angle);
	void Move();
	void Fire();
	void Dead();
	void FireSkill_01();
	void FireSkill_02(Enemy* Enemy);

	//get set
	inline const FPOINT Getpos() { return this->pos; }  
	int GetMissileCount() { return missileCount; }
	Missile* GetMissile() { return this->missile; }
	//FPOINT형으로 Tank의 좌표를 GetFpoint() 받아오는 함수
};

