#pragma once
#include "GameNode.h"
#define ASTAR_TILE_SIZE     30
#define ASTAR_TILE_COUNT    20
enum class AstarTileType 
{
    Start,End,Wall,None
};
class AstarTile :public GameNode 
{
private:
    int idx, idy;
    POINT center;
    RECT rc;

    float costFromStart;        // G : 시작점부터 현재 노드까지의 비용
    float costToGoal;           // H : 현재 노드부터 목적지까지의 예상 비용
    float totalCost;            // F : G + H



    bool visited;
    AstarTile* parentTile;      // 이전 노드 G가 갱신될 때마다 이전 노드를 갱신

    COLORREF color;
    HBRUSH hBrush;
    HBRUSH hOldBrush;
    AstarTileType type;
public:
    virtual HRESULT Init();
    HRESULT Init(int idX, int idY);
    virtual void Release();
    virtual void Update();
    virtual void Render(HDC hdc);
    RECT GetRect() { return this->rc; }
    int GetidX(){  return this->idx; }
    int GetidY() {return this->idy; }
    void SetidX(int idx) { this->idx = idx; }
    void SetidY(int idy) { this->idy = idy; }
    bool GetVisited() { return this->visited; }
    void SetcostFromStart(int num) {this->costFromStart= num;}
    void SetcostToGoal(int num) { this->costToGoal = num; }
    void SettotalCost(int num) { this->totalCost = num; }
    int GetcostFromStart() { return this->costFromStart; }
    int GetcostToGoal() { return this->costToGoal; }
    int GettotalCost() { return this->totalCost; }
    void SetVisited(bool visited) { this->visited = visited; }
    void SetColor(COLORREF color);
    void SetType(AstarTileType type) { this->type = type; }
    AstarTileType GetType() { return this->type; }

    virtual ~AstarTile() {};
};
typedef struct tag_create
{
    bool activeOn = false;
}Create;
class AstarScene :
    public GameNode
{
    //이차원 배열 맵을 구성
    AstarTile map[ASTAR_TILE_COUNT][ASTAR_TILE_COUNT];
    RECT rcMain;
    AstarTile* startTile; // 처음 타일
    AstarTile* destTile;  // 목표 타일

    AstarTile* currTile;  // 후보타일을 선정할 떄의 기준타일

    vector<AstarTile*> openList; // 
    vector<AstarTile*> closeList; //더이상 계산이 필요없는 노드의 모음
public :
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render(HDC hdc);

    void FindPath(); // 후보정하기
    void AddOpenList(AstarTile* currTile);
    void CreateWall();
    virtual ~AstarScene() {};
};

