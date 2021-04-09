#pragma once
#include "GameNode.h"


class Missile;
class MissileManager :public GameNode
{
public:
    enum MISSILETYPE
    {
        SKILL1,
        SKILL2,
        END
    };
private:
    vector<Missile*> vMissile;
public:
    MISSILETYPE missile;
    HRESULT Init();
    void Release();
    void Update();
    void Render(HDC hdc);


};

