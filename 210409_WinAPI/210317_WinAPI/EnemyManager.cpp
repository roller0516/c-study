#include "EnemyManager.h"
#include "Enemy.h"
HRESULT EnemyManager::Init()
{
    //배열 []
    //vector push_back() -> 값을 넣음
    for (int i = 0; i < 1; i++) 
    {
        vEnemys.push_back(new Enemy);
        /*vEnemys[i]->Init(100+(i%5)*200,100+(i/5)*100);*/
        vEnemys[i]->Init(WINSIZE_X / 2, WINSIZE_Y / 2);
    }

    return S_OK;
}

void EnemyManager::Release()
{
   //반복자(iterator) : STL 자료구조를 구성하는 원소의 메모리를 저장하는 객체
    vector<Enemy*>::iterator iter;
    for (iter = vEnemys.begin(); iter!=vEnemys.end(); iter++)
    {
        (*iter)->Release();
        delete (*iter);
        (*iter) = nullptr;
    }
}

void EnemyManager::Update()
{
    vector<Enemy*>::iterator iter;
    for (iter = vEnemys.begin(); iter != vEnemys.end(); iter++)
    {
        (*iter)->Update();
    }
}

void EnemyManager::Render(HDC hdc)
{
    vector<Enemy*>::iterator iter;
    for (iter = vEnemys.begin(); iter != vEnemys.end(); iter++)
    {
        (*iter)->Render(hdc);
    }
}

void EnemyManager::AddEenmey()//구현
{
    vEnemys.resize(10);
    for (int i = 0; i < vEnemys.size(); i++)
    {
        vEnemys.push_back(new Enemy);
    }
}

