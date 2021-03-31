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
	int elapsedTime;	// 100이 될 때마다 애니메이션 프레임을 1씩 증가
	int frame;			// 애니메이션 프레임 0 ~ 8
	int StateType;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

};

