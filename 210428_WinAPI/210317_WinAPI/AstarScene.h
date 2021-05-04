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

    float costFromStart;        // G : ���������� ���� �������� ���
    float costToGoal;           // H : ���� ������ ������������ ���� ���
    float totalCost;            // F : G + H



    bool visited;
    AstarTile* parentTile;      // ���� ��� G�� ���ŵ� ������ ���� ��带 ����

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
    //������ �迭 ���� ����
    AstarTile map[ASTAR_TILE_COUNT][ASTAR_TILE_COUNT];
    RECT rcMain;
    AstarTile* startTile; // ó�� Ÿ��
    AstarTile* destTile;  // ��ǥ Ÿ��

    AstarTile* currTile;  // �ĺ�Ÿ���� ������ ���� ����Ÿ��

    vector<AstarTile*> openList; // 
    vector<AstarTile*> closeList; //���̻� ����� �ʿ���� ����� ����
public :
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render(HDC hdc);

    void FindPath(); // �ĺ����ϱ�
    void AddOpenList(AstarTile* currTile);
    void CreateWall();
    virtual ~AstarScene() {};
};

