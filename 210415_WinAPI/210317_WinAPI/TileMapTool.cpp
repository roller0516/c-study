#include "TileMapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "BattleScene.h"



HRESULT TileMapTool::Init()
{

    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);

    TileImage = ImageManager::GetSingleton()->AddImage("샘플타일",
        "Image/maptiles.bmp", 640, 288,
        SAMPLE_TILE_X, SAMPLE_TILE_Y);

    for (int i = 0; i < TILE_Y; i++) 
    {
        for (int j = 0; j < TILE_X; j++) 
        {
            tileInfo[i * TILE_X + j].frameX = 1;
            tileInfo[i * TILE_X + j].frameY = 1;

            tileInfo[i * TILE_X + j].rcTile.left = TILESIZE * j;
            tileInfo[i * TILE_X + j].rcTile.top = TILESIZE * i;
            tileInfo[i * TILE_X + j].rcTile.right = 
                tileInfo[i * TILE_X + j].rcTile.left + TILESIZE;
            tileInfo[i * TILE_X + j].rcTile.bottom = 
                tileInfo[i * TILE_X + j].rcTile.top + TILESIZE;
        }
    }

    return S_OK;
}

void TileMapTool::Release()
{
}

void TileMapTool::Update()
{
    //마우스 왼쪽 버튼 클릭시 좌표 사용
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)) 
    {
        for (int i = 0; i < TILE_X * TILE_Y; i++) 
        {
            if (PtInRect(&tileInfo[i].rcTile, g_hMouse)) 
            {
                selectedFrameX = i % TILE_X;
                selectedFrameY = i / TILE_X;

                break;
            }
        }
    }
        
}

void TileMapTool::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0,TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);
    TileImage->Render(hdc, TILEMAPTOOLSIZE_X - TileImage->GetWidth(),0);

    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            TileImage->FrameRender(hdc,
                tileInfo[i * TILE_X + j].rcTile.left,
                tileInfo[i * TILE_X + j].rcTile.top,
                tileInfo[i * TILE_X + j].frameX,
                tileInfo[i * TILE_X + j].frameY);
        }
    }
}

