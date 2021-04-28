#pragma once
#include "GameNode.h"

/*
	�Լ� ������ : �Լ��� ...

	(����) ������ : ������ �޸��ּҸ� ���� �� �ִ� (������ ������) ����

	int a = 10;
	int* pA = &a;

	void sum(int a, int b);

	void (*funcPointer)(int, int);	// �Լ�������(����) ����

	funcPointer = sum;
	sum(10, 20);
	funcPointer(10, 20);

	void Print(void);

	void (*funcPrint)(void);
	funcPrint = Print;
	//funcPrint = sum;		�Լ������� (����) = �Լ��� �ּ� ����
	funcPrint();

*/

enum class ButtonState
{
	NONE, DOWN, UP
};

typedef void (*func_t)(int);
typedef void (*func_t2)(void);

class Image;
class Button : public GameNode
{
private:
	ButtonState state;
	Image* img;
	RECT rc;
	POINT pos;
	
	func_t func;
	func_t2 func2;
	int func_arg;

	//void (*func_t)(int); // void Save(int stageNum);

public:
	HRESULT Init(const char* fileName, int posX, int posY);
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetFunc(func_t2 func2)
	{
		this->func2 = func2;
	}

	void SetFunc(func_t func, int funcArg)
	{
		this->func = func; this->func_arg = funcArg;
	}
	
	int Getfunc_arg() {
		return this->func_arg;
	}
	//void SetFunc(void (*func_t)(int)) { this->func_t = func_t; }

	virtual ~Button() {};
};

