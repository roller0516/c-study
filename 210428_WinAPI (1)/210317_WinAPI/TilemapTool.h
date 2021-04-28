#pragma once
#include "GameNode.h"

// 샘플 타일 정보
// 640 * 288
class Button;
class Image;
class TilemapTool : public GameNode
{
private:
	// 샘플 타일 이미지
	Image* sampleTile;
	TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;

	// 메인타일의 정보
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

