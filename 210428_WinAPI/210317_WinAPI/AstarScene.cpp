#include "AstarScene.h"

HRESULT AstarTile::Init()
{
    return S_OK;
}
HRESULT AstarTile::Init(int idX, int idY)
{
    this->idx = idX;
    this->idy = idY;

    center.x = idX * ASTAR_TILE_SIZE + (ASTAR_TILE_SIZE / 2);
    center.y = idY * ASTAR_TILE_SIZE + (ASTAR_TILE_SIZE / 2);

    rc.left = idX * ASTAR_TILE_SIZE;
    rc.right = rc.left + ASTAR_TILE_SIZE;
    rc.top = idY * ASTAR_TILE_SIZE;
    rc.bottom = rc.top + ASTAR_TILE_SIZE;

    costFromStart = 0.0f;
    costToGoal = 0.0f;
    totalCost = 0.0f;

    type = AstarTileType::None;

    parentTile = nullptr;

    color = RGB(100, 100, 100);
    hBrush = CreateSolidBrush(color);

    return S_OK;
}
void AstarTile::Release()
{
    DeleteObject(hBrush);
}

void AstarTile::Update()
{

}

void AstarTile::Render(HDC hdc)
{
    hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
    FillRect(hdc,&rc,hBrush);
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

    SelectObject(hdc, hOldBrush);
}

void AstarTile::SetColor(COLORREF color)
{
    this->color = color;
    DeleteObject(hBrush);
    hBrush = CreateSolidBrush(color);
}

HRESULT AstarScene::Init()
{
    for (int i = 0; i < ASTAR_TILE_COUNT; i++) //세로반복 
    {
        for (int j = 0; j < ASTAR_TILE_COUNT; j++) //가로반복 
        {
            map[i][j].Init(j, i);
        }
    }
    startTile =     &map[2][2];
    destTile  =     &map[19][19];
    currTile = startTile;

    startTile->SetColor(RGB(255, 0, 0));
    startTile->SetType(AstarTileType::Start);
    destTile->SetColor(RGB(0, 0, 255));
    destTile->SetType(AstarTileType::End);
    return S_OK;
}

void AstarScene::Release()
{
}

void AstarScene::Update()
{
    CreateWall();
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
        FindPath();
}

void AstarScene::Render(HDC hdc)
{
    for (int i = 0; i < ASTAR_TILE_COUNT; i++) //세로반복 
    {
        for (int j = 0; j < ASTAR_TILE_COUNT; j++) //가로반복 
        {
            map[i][j].Render(hdc);
        }
    }
}

void AstarScene::FindPath() // 비용 위 아래 오 왼 10 대각선 14
{ 
    if (currTile) 
    {
        //주위에 있는 이동 가능한 타일들을 F값 계산 후보에 넣는다.
        AddOpenList(currTile);
        currTile->SetVisited(true);
        int min = 100000;
        int minIndex = -1;
        //후보들 중 F값이 가장 작은 작은 타일을 다음 currTile로 선정
        //F값을 비교한다*/
        for (int i = 0; i < openList.size(); i++) 
        {
            int chaiX = abs(destTile->GetidX() - openList[i]->GetidX());
            int chaiY = abs(destTile->GetidY() - openList[i]->GetidY());
            float c;
            c=sqrt((chaiX * chaiX) + (chaiY * chaiY));
            openList[i]->SetcostToGoal(c);

            openList[i]->SettotalCost(openList[i]->GetcostFromStart() + openList[i]->GetcostToGoal());
            if (openList[i]->GetcostToGoal() < min)
            {
                minIndex = i;
                min = openList[i]->GetcostToGoal();
            }
        }
        currTile = openList[minIndex];
        openList.erase(openList.begin() + minIndex);
        currTile->SetColor(RGB(255, 0, 0));
        //도착 여부 판단 return
        if (currTile->GetidX() == destTile->GetidX() && currTile->GetidY() == destTile->GetidY())
        {
            return;
        }

        //G값이 갱신되는지 판단(parentTile도 갱신)

        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
         FindPath();
    }
}

void AstarScene::AddOpenList(AstarTile* currTile)
{
    //벽이 아니고 closeList에 없는 타일들을 후보에 넣는다.
    //주의 8개를 비교
    for (int i = currTile->GetidY()-1; i < currTile->GetidY() +2; i++)
    {
        for (int j = currTile->GetidX()-1; j < currTile->GetidX() +2; j++)
        {
            if (i == currTile->GetidX() && j == currTile->GetidY()) continue;
            int x, y;
            //x
            if (currTile->GetidX() > j) x = currTile->GetidX() - 1;
            else if (currTile->GetidX() < j) x = currTile->GetidX() + 1;
            else x = currTile->GetidX();
            //y
            if (currTile->GetidY() > i) y = currTile->GetidY() - 1;
            else if (currTile->GetidY() < i) y = currTile->GetidY() + 1;
            else y = currTile->GetidY();

            int chaiX = abs( x - currTile->GetidX());
            int chaiY = abs( y - currTile->GetidY());

            //대각선이냐
            if (chaiX >0  && chaiY >0 )
                map[y][x].SetcostFromStart(14);
            else     //위 아래 왼 오
                map[y][x].SetcostFromStart(10);
       
            if (map[y][x].GetType() != AstarTileType::Wall && map[y][x].GetVisited() == false)
            {
                map[y][x].SetColor(RGB(255, 100, 100));
                openList.push_back(&map[y][x]);
            }
        }
    }
}

void AstarScene::CreateWall()
{
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)
        || KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
    {
        int posX = g_ptMouse.x / ASTAR_TILE_SIZE;
        int posY = g_ptMouse.y / ASTAR_TILE_SIZE;
        if (0 <= posX && posX < ASTAR_TILE_COUNT && 0 <= posY && posY < ASTAR_TILE_COUNT) 
        {
            if (map[posY][posX].GetType() != AstarTileType::Start && map[posY][posX].GetType() != AstarTileType::End)
            {
                map[posY][posX].SetColor(RGB(255, 255, 0));
                map[posY][posX].SetType(AstarTileType::Wall);
            }
        }
    }


}
