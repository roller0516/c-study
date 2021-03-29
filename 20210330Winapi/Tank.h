#pragma once
#include "GameNode.h"
//#include "MainGame.h"
//#include "Missile.h"

/*
	is-a ����		��ũ�� ���ӳ���̴�.
	has-a ����		��ũ�� �̻����� ������ �ִ�.
					���� ��ũ�� ��ǥ�� �������ִ�.
*/
class Enemy;
class Missile;		// ���漱��
class Tank : public GameNode
{
private: // ���
	// �Ӽ� : �������
	FPOINT pos;

	int size;
	float attackValue;
	string name;
	RECT shape;

	// ����
	// ������ ������, ����
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;	

	// �̻���
	int missileCount;
	Missile* missile;		// 2
	
//* -> �ּ�! �����迭�Ҷ��� ������ 
	//[]�迭  * �������� 
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
	//FPOINT������ Tank�� ��ǥ�� GetFpoint() �޾ƿ��� �Լ�
};

