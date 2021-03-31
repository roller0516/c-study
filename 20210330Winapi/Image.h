#pragma once
#include "config.h"
class Image
{
public :
	enum  IMAGE_LOAD_KIND
	{
		RESOURCE,	//프로젝트 자체에 포함 시킬 이미지
		FILE,		// 외부에서 로드할 이미지
		EMPTY,		//자체 생산 이미지 색조합시, 색을뺄때,
		END  
	};

	typedef struct tageImageInfo 
	{
		DWORD resID;		//리소스의 고유한 ID
		HDC hMemDC;			//그리기를 주관하는 핸들
		HBITMAP hBitmap;	//이미지 정보
		HBITMAP hOldBit;	//기존 이미지 정보
		int width;			//이미지 가로 크기
		int height;			//이미지 세로 크기
		BYTE loadType;		//로드타입
		tageImageInfo() 
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;
		}

	}IMAGE_INFO,*LPIMAGE_INFO;
private:
	IMAGE_INFO* imageInfo;
public:
	//빈 비트맵 이미지를 만드는 함수
	HRESULT Init(int width, int height);
	//파일로부터 이미지를 로드 하는 함수
	HRESULT Init(const char* fileName, int width, int height);
	void Release();
	void Render(HDC hdc);
};

