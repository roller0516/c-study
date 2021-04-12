#include "EnemyManager.h"
#include "Enemy.h"
HRESULT EnemyManager::Init()
{
    //�迭 []
    //vector push_back() -> ���� ����
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
   //�ݺ���(iterator) : STL �ڷᱸ���� �����ϴ� ������ �޸𸮸� �����ϴ� ��ü
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

void EnemyManager::AddEenmey()//����
{
    vEnemys.resize(10);
    for (int i = 0; i < vEnemys.size(); i++)
    {
        vEnemys.push_back(new Enemy);
    }
}

