#include "TilemapTool.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Button.h"
#include "BattleScene.h"
TILE_INFO TilemapTool::tileInfo[TILE_X * TILE_Y];
int TilemapTool::count = 1;
HRESULT TilemapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);

    sampleTile = ImageManager::GetSingleton()->AddImage(
        "����Ÿ��", "Image/maptiles.bmp", 640, 288,
        SAMPLE_TILE_X, SAMPLE_TILE_Y);

    hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

    // ���� ���� ��Ʈ ����
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            tileInfo[i * TILE_X + j].frameX = 3;
            tileInfo[i * TILE_X + j].frameY = 0;

            tileInfo[i * TILE_X + j].rcTile.left = TILESIZE * j;
            tileInfo[i * TILE_X + j].rcTile.top = TILESIZE * i;
            tileInfo[i * TILE_X + j].rcTile.right = 
                tileInfo[i * TILE_X + j].rcTile.left + TILESIZE;
            tileInfo[i * TILE_X + j].rcTile.bottom = 
                tileInfo[i * TILE_X + j].rcTile.top + TILESIZE;
        }
    }

    // ���� ���� ��Ʈ ����
    for (int i = 0; i < SAMPLE_TILE_Y; i++)
    {
        for (int j = 0; j < SAMPLE_TILE_X; j++)
        {
            SetRect(&sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile,
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j),
                (TILESIZE * i),
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j) + TILESIZE,
                (TILESIZE * i) + TILESIZE);

            sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
            sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;

            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left =
            //    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j);
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top = (TILESIZE * i);
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.right =
            //    sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left + TILESIZE;
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.bottom =
            //    sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top + TILESIZE;
        }
    }
    // UI Button
    ImageManager::GetSingleton()->AddImage("�����ư", "Image/SaveImage.bmp",
        1282/10, 726/10, 1, 2);
    ImageManager::GetSingleton()->AddImage("�ҷ������ư", "Image/LoadImage.bmp",
        1286/10, 724/10, 1, 2);
    ImageManager::GetSingleton()->AddImage("������ư", "Image/SaveImage.bmp",
        1282 / 10, 726 / 10, 1, 2);
    ImageManager::GetSingleton()->AddImage("������ư", "Image/LoadImage.bmp",
        1286 / 10, 724 / 10, 1, 2);

    btnSave = new Button();
    btnSave->Init("�����ư", 750,
       200);
     btnSave->SetFunc(Save, count);

    btnLoad = new Button();
    btnLoad->Init("�ҷ������ư", 750,
        300);
    btnLoad->SetFunc(Load, count);

    btnNext = new Button();
    btnNext->Init("������ư",800,
        500);
    btnNext->SetFunc(StageUp);
    btnPrev = new Button();
    btnPrev->Init("������ư", 1000,
        500);
    btnPrev->SetFunc(StageDown);
    return S_OK;
}

void TilemapTool::Release()
{
    SAFE_RELEASE(btnSave);
    SAFE_RELEASE(btnLoad);
}

void TilemapTool::Update()
{
    // ���̺� F1 F2 F3 ...
    //int stageNum = VK_F1;
    //int currInputKey;
    if (btnSave)    btnSave->Update();
    if (btnLoad)    btnLoad->Update();
    if (btnNext)    btnNext->Update();
    if (btnPrev)    btnPrev->Update();

    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_CONTROL))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            /*btnLoad->SetFunc(Load, 1);*/
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
        {
            /*btnLoad->SetFunc(Load, 2);*/
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
        {
            /*btnLoad->SetFunc(Load, 3);*/
        }
    }
    else
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
           /* btnSave->SetFunc(Save, 1);*/
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
        {
            /*btnSave->SetFunc(Save, 2);*/
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
        {
           /* btnSave->SetFunc(Save, 3);*/
        }
    }

    // ���� ���� ���
    rcMain.left = 0;
    rcMain.top = 0;
    rcMain.right = rcMain.left + (TILESIZE * TILE_X);
    rcMain.bottom = rcMain.top + (TILESIZE * TILE_Y);

    // ���� ���� ���
    rcSample.left = TILEMAPTOOLSIZE_X - sampleTile->GetWidth();
    rcSample.top = 0;
    rcSample.right = TILEMAPTOOLSIZE_X;
    rcSample.bottom = sampleTile->GetHeight();

    if (PtInRect(&rcMain, g_ptMouse))
    {
        // ���콺 ���� ��ư Ŭ���� ��ǥ ���
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)
            || KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            for (int i = 0; i < TILE_X * TILE_Y; i++)
            {
                if (PtInRect(&(tileInfo[i].rcTile), g_ptMouse))
                {
                    //selectedFrameX = i % TILE_X;
                    //selectedFrameY = i / TILE_X;

                    tileInfo[i].frameX = ptStartSelectedFrame.x;
                    tileInfo[i].frameY = ptStartSelectedFrame.y;

                    for (int j = 0; j <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; j++)
                    {
                        for (int k = 0; k <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; k++)
                        {
                            if ((i % TILE_X) + k >= TILE_X) continue;
                            if ((i / TILE_X) + j >= TILE_Y) continue;

                            tileInfo[i + j * TILE_X + k].frameX = ptStartSelectedFrame.x + k;
                            tileInfo[i + j * TILE_X + k].frameY = ptStartSelectedFrame.y + j;
                        }
                    }

                    break;
                }
            }
        }
    }
    else if (PtInRect(&rcSample, g_ptMouse))
    {
        // ���콺 ���� ��ư Ŭ���� ��ǥ ���
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            // 2) ���콺 ��ǥ�� �ε��� ���
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptStartSelectedFrame.x = posX / TILESIZE;
            ptStartSelectedFrame.y = posY / TILESIZE;

            ptSelected[0] = g_ptMouse;

            //// 1) ��� Ÿ���� �ݺ��ϸ鼭 ��Ʈ�浹 Ȯ��
            //for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
            //{
            //    if (PtInRect(&(sampleTileInfo[i].rcTile), g_ptMouse))
            //    {
            //        ptStartSelectedFrame.x = i % SAMPLE_TILE_X;
            //        ptStartSelectedFrame.y = i / SAMPLE_TILE_X;

            //        break;
            //    }
            //}
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
        {
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptEndSelectedFrame.x = posX / TILESIZE;
            ptEndSelectedFrame.y = posY / TILESIZE;

            // ���ÿ��� �ʱ�ȭ
            ptSelected[0].x = -1;
            ptSelected[0].y = -1;
            ptSelected[1].x = -1;
            ptSelected[1].y = -1;
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            ptSelected[1] = g_ptMouse;
        }
    }

}

void TilemapTool::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0,
        TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    // ����Ÿ�� ��ü
    sampleTile->Render(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth(), 0);

    // ���� ���� ǥ��
    hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);
    Rectangle(hdc, ptSelected[0].x, ptSelected[0].y, ptSelected[1].x, ptSelected[1].y);
    SelectObject(hdc, hOldSelectedBrush);

    // UI Button
    if (btnSave)    btnSave->Render(hdc);
    if (btnLoad)    btnLoad->Render(hdc);
    if (btnNext)    btnNext->Render(hdc);
    if (btnPrev)    btnPrev->Render(hdc);

    // ���ο��� ��ü
    for (int i = 0; i < TILE_X * TILE_Y; i++)
    {
        sampleTile->FrameRender(hdc,
            tileInfo[i].rcTile.left,
            tileInfo[i].rcTile.top,
            tileInfo[i].frameX,
            tileInfo[i].frameY);
    }

    // ���õ� Ÿ��
    if (ptStartSelectedFrame.x == ptEndSelectedFrame.x &&
        ptStartSelectedFrame.y == ptEndSelectedFrame.y)
    {
        sampleTile->FrameRender(hdc, 
            TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
            sampleTile->GetHeight() + 50, 
            ptStartSelectedFrame.x, ptStartSelectedFrame.y, false, 3);
    }
    else
    {
        for (int i = 0; i <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; i++)
        {
            for (int j = 0; j <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; j++)
            {
                sampleTile->FrameRender(hdc,
                    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (j * TILESIZE),
                    sampleTile->GetHeight() + 50 + (i * TILESIZE),
                    ptStartSelectedFrame.x + j, ptStartSelectedFrame.y + i, false, 1);

            }
        }
    }

}

/*
    �ǽ�1. F1, F2, F3  �� Ű�� ������ �� 
    Save/saveMapData1.map, Save/saveMapData2.map, Save/saveMapData3.map
    �� �� ���Ͽ� ����� �� �ֵ��� �ڵ� ����

    �ǽ�2. �ε�� Ctrl + F1, ... 
*/

void TilemapTool::Save(int stageNum)
{
    string fileName = "Save/saveMapData";  // 1.map";
    fileName += to_string(count) + ".map";
    DWORD writtenBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0,
        0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
        &writtenBytes, NULL);

    CloseHandle(hFile);
}

void TilemapTool::Load(int stageNum, TILE_INFO* tileInfo)
{
    string fileName = "Save/saveMapData";  // 1.map";
    fileName += to_string(count) + ".map";
     
    DWORD readBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0,
        0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
        &readBytes, NULL))
    {
        
    }
    else
    {
        MessageBox(g_hWnd, "�������� �ε� ����", "����", MB_OK);
    }

    CloseHandle(hFile);
}

void TilemapTool::Load(int stageNum)
{
    string fileName = "Save/saveMapData";  // 1.map";
    fileName += to_string(count) + ".map";

    DWORD readBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0,
        0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
        &readBytes, NULL))
    {

    }
    else
    {
        MessageBox(g_hWnd, "�������� �ε� ����", "����", MB_OK);
    }
}

void TilemapTool::StageUp()
{
    count++;
}

void TilemapTool::StageDown()
{
    count--;
    if (count  <1)
        count = 1;
}
