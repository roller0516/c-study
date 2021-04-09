#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "Image.h"
HRESULT Enemy::Init()
{
    image = new Image();

    if (FAILED(image->Init("Image/ufo.bmp", 530, 32, 10,1,true , RGB(255, 0, 255))))
    {
        MessageBox(g_hWnd, "Image/ufo.bmp 로드 실패", "실패 ", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    elapsedTime = 0;
    pos.x =  0.0f;
    pos.y = 0.0f;
    size = 80;
    name = "NormalEnemy";
    shape = { 0, 0, 0, 0 };
    moveSpeed = 3.3f;
    isAlive = true;
    angle = 0.0f;
    target = nullptr;
    dir = 1;

    return S_OK;
}

void Enemy::Release()
{
    if (image) 
    {
        image->Release();
        delete image;
        image = nullptr;
    }
}

void Enemy::Update()
{
    elapsedTime++;
    if (elapsedTime >= 5) 
    {
        currFrameX++;
        if (currFrameX >= 10)
        {
            currFrameX = 0;
        }
        elapsedTime = 0;
    }
    
    
    if (isAlive)
    {
        //HorizonMove();
        //Move();
    }
}

void Enemy::Render(HDC hdc)
{
    if (isAlive)
    {
        if (image)
            image->FrameRender(hdc, pos.x, pos.y, currFrameX);
    }
}

void Enemy::Move()
{
    if (target)
    {
        FPOINT targetPos = target->GetPos();

        // 현재 위치에서 타겟 위치로 이동할 수 있는 각도 구하기
        float x = targetPos.x - pos.x;
        float y = targetPos.y - pos.y;

        angle = atan2(y, x);

        pos.x += cosf(angle) * moveSpeed;
        pos.y += sinf(angle) * moveSpeed;
    }
}

void Enemy::HorizonMove()
{
    if (pos.x > WINSIZE_X || pos.x < 0)
    {
        dir *= -1;
    }
    pos.x += moveSpeed * dir;
}
