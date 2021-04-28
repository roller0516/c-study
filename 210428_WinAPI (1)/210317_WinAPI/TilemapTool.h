#pragma once
#include "GameNode.h"

// ���� Ÿ�� ����
// 640 * 288
class Button;
class Image;
class TilemapTool : public GameNode
{
private:
	// ���� Ÿ�� �̹���
	Image* sampleTile;
	TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;

	// ����Ÿ���� ����
	static TILE_INFO tileInfo[TILE_X * TILE_Y];
	RECT rcMain;

	POINT ptStartSelectedFrame;
	POINT ptEndSelectedFrame;

	POINT ptSelected[2];
	HBRUSH hSelectedBrush;
	HBRUSH hOldSelectedBrush;

	// UI button
	Button* btnSave;
	Button* btnLoad;
	Button* btnNext;
	Button* btnPrev;
	
	
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static int count;
	
	static void Save(int stageNum);
	static void Load(int stageNum, TILE_INFO* tileInfo);
	static void Load(int stageNum);
	static void StageUp();
	static void StageDown();

	virtual ~TilemapTool() {};
};

