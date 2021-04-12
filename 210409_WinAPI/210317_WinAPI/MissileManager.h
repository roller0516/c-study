#pragma once
#include "GameNode.h"

class Enemy;
class Missile;
class MissileManager :public GameNode
{
public:
    enum MISSILETYPE
    {
        PATTERN1,
        PATTERN2,
        END
    };
private:
    vector<Missile*> vMissile;
    float angle;
    int fireIndex;
    int count;
    int elapsedTime;
    int timer;
    Enemy* owner;
    bool isSkillon;
public:
    MISSILETYPE missile;
    HRESULT Init(Enemy* owner);
    void Release();
    void Update();
    void Render(HDC hdc);
    void FireSkill_01(FPOINT enemyPos);
    void FireSkill_02(Enemy* owner);
    void Fire();
    void SetPos(FPOINT enemyPos);
    void SetSkillOn(bool skill) { this->isSkillon = skill; }
    bool GetIsSkillon() { return this->isSkillon; }
};

