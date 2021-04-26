#pragma once
#include "GameNode.h"

// 640 * 288
#define SAMPLE_TILE_X	20
#define SAMPLE_TILE_Y	9
#define TILESIZE		32

//���� �׸��� ���� ����
#define TILE_X			20
#define TILE_Y			20

typedef struct tagTile
{
	RECT rcTile;
	int frameX;
	int frameY;
}TILE_INFO;

class Image;
class TileMapTool :public GameNode
{
private :
	//���� Ÿ���� ����
	TILE_INFO tileInfo[TILE_X* TILE_Y];
	//���� Ÿ�� �̹���
	Image* TileImage;

	int selectedFrameX;
	int selectedFrameY;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

