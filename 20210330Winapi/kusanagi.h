#pragma once
#include "GameNode.h"
class Image;
class Kusanagi :public GameNode
{
	enum WALKSTATE
	{
		IDLE,
		RIGHT,
		LEFT,
		END
	};
private:
	Image* img;
	FPOINT pos;
	int elapsedTime;	// 100�� �� ������ �ִϸ��̼� �������� 1�� ����
	int frame;			// �ִϸ��̼� ������ 0 ~ 8
	int StateType;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

