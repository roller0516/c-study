#include "MissileManager.h"
#include "Missile.h"
#include "Enemy.h"
HRESULT MissileManager::Init(Enemy* owner)
{
    this->owner = owner;
    vMissile.resize(100);
    vector<Missile*>::iterator iter;
    for (iter = vMissile.begin(); iter != vMissile.end(); iter++) 
    {
        (*iter) = new Missile();
        (*iter)->Init(/*this->owner*/);

        //미사일 매니저를 들고 있는 적 객체의 정보를 전달
    }
    isSkillon = false;
    return S_OK;
}

void MissileManager::Release()
{
    vector<Missile*>::iterator iter;
    for (iter = vMissile.begin(); iter != vMissile.end(); iter++)
    {
        (*iter)->Release();
        delete (*iter);
        (*iter) = nullptr;
    }
    vMissile.clear();
}

void MissileManager::Update()
{
    vector<Missile*>::iterator iter;
    for (iter = vMissile.begin(); iter != vMissile.end(); iter++)
    {
        (*iter)->Update();
    }

    //[0]~ [99] ->update();
    
    if (isSkillon)
    {
        FireSkill_02(this->owner);
        vector<Missile*>::iterator iter2 = vMissile.begin();
        iter2[timer]->SetDraw(true);
        timer++;
        if (timer >= 100)
        {
            timer = 0;
            isSkillon = false;
            for (iter2; iter2 != vMissile.end(); iter2++)
            {
               (*iter2)->SetType((*iter2)->StarMoving);
               (*iter2)->SetIsFired(true);
            }
        }
    }
}
  
    

void MissileManager::Render(HDC hdc)
{
    vector<Missile*>::iterator iter;
    for (iter = vMissile.begin(); iter != vMissile.end(); iter++)
    {
        (*iter)->Render(hdc);
    }
}
void MissileManager::FireSkill_01(FPOINT enemyPos)
{
    // 1. 미사일을 36발을 쏘고 일정 높이 이상 올라가면 36방향으로 퍼지게 한다.
    int firedCount = 0;
    for (int i = 50; i < count; i++)
    {
        if (firedCount < 36 && vMissile[i]->GetIsFired() == false)
        {
            vMissile[i]->SetType(Missile::TYPE::Skill_01);
            vMissile[i]->SetDraw(true);
            vMissile[i]->SetIsFired(true);
            vMissile[i]->SetPos(enemyPos);
            vMissile[i]->SetFireIndex(firedCount);

            angle -= 0.1f;

            firedCount++;
        }
    }
    firedCount = 0;
    for (int i = 100; i < count; i++)
    {
        if (firedCount < 36 && vMissile[i]->GetIsFired() == false)
        {
            vMissile[i]->SetType(Missile::TYPE::Skill_01);
            vMissile[i]->SetDraw(true);
            vMissile[i]->SetIsFired(true);
            vMissile[i]->SetAngle(angle);
            vMissile[i]->SetPos(enemyPos.x+100, enemyPos.y+100);
            vMissile[i]->SetFireIndex(firedCount);

            firedCount++;
        }
    }

    // 2. 미사일을 한발 쏘고 일정 높이 이상 올라가면 36발을 호출한다.
}

void MissileManager::FireSkill_02(Enemy* owner)
{
    int firedCount = 0;
    FPOINT targetPos;
    targetPos.x = this->owner->GetPos().x+70;
    targetPos.y = this->owner->GetPos().y;

    vector<Missile*>::iterator iter;
    for (iter = vMissile.begin(); *iter != vMissile[50] ; iter++)
    {
        if (firedCount < 10 && (*iter)->GetIsFired()==false)
        {
            (*iter)->SetPos(targetPos.x -= cosf(DegToRadian(0))*10 , targetPos.y);
            (*iter)->SetFireIndex(firedCount);
            firedCount++; // 0~ 9;
        }
        else if (firedCount >= 10 && firedCount < 20 && (*iter)->GetIsFired() == false) //9~ 19
        {
             (*iter)->SetPos(targetPos.x += cosf(DegToRadian(36.0f)) * 10,
                targetPos.y -= sinf(DegToRadian(36.0f)) * 10);
            (*iter)->SetFireIndex(firedCount);
            firedCount++; 
        }
        else if (firedCount >= 20 && firedCount < 30 && (*iter)->GetIsFired() == false)
        {
            (*iter)->SetPos(targetPos.x -= cosf(DegToRadian(72.0f)) * 10,
                targetPos.y += sinf(DegToRadian(72.0f)) * 10);
            (*iter)->SetFireIndex(firedCount);
            firedCount++; 
        }
        else if (firedCount >= 30 && firedCount < 40 && (*iter)->GetIsFired() == false)
        {
            (*iter)->SetPos(targetPos.x -= cosf(DegToRadian(72.0f)) * 10,
                targetPos.y -= sinf(DegToRadian(72.0f)) * 10);
            (*iter)->SetFireIndex(firedCount);
            firedCount++; 
        }
        else if (firedCount >= 40 && firedCount < 50 && (*iter)->GetIsFired() == false)
        {
            (*iter)->SetPos(targetPos.x -= cosf(DegToRadian(-144.0f)) * 10,
                targetPos.y -= sinf(DegToRadian(-144.0f)) * 10);
            (*iter)->SetFireIndex(firedCount);
            firedCount++;
        } 
    }   
}

void MissileManager::Fire()
{
    vector<Missile*>::iterator iter;
    for (iter = vMissile.begin(); iter != vMissile.end(); iter++)
    {
        if ((*iter)->GetIsFired() == false) 
        {
            (*iter)->SetDraw(true);
            (*iter)->SetIsFired(true);
            (*iter)->SetAngle(DegToRadian(-90));
            break;
        }
    }
}





