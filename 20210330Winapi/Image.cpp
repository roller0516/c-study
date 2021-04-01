
#include "Image.h"

HRESULT Image::Init(int width, int height)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = CreateCompatibleBitmap(hdc, width, height);
	imageInfo->hOldBit = 
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::EMPTY;
	isTransparent = false;

	ReleaseDC(g_hWnd, hdc);
	AnimationIndex = 0;
	if (imageInfo->hBitmap == NULL) 
	{
		Release();
		return E_FAIL;
	}

	this->isTransparent = FALSE;
	this->transColor = FALSE;

	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
	HDC hdc = GetDC(g_hWnd);

	imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height,LR_LOADFROMFILE);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;
	AnimationIndex = 0;
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}


	this->isTransparent = isTransparent;
	this->transColor = transColor;


	return S_OK;
}

HRESULT Image::Init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY,bool isTransparent, COLORREF transColor)
{
	
	HDC hdc = GetDC(g_hWnd); // hdc 

	imageInfo = new IMAGE_INFO();
	imageInfo->resID = 0;
	imageInfo->hMemDC = CreateCompatibleDC(hdc);
	imageInfo->hBitmap = (HBITMAP)LoadImage(g_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	imageInfo->hOldBit =
		(HBITMAP)SelectObject(imageInfo->hMemDC, imageInfo->hBitmap);
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->loadType = IMAGE_LOAD_KIND::FILE;

	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->frameWidth = width / maxFrameX;
	imageInfo->frameHeight = height / maxFrameY;

	imageInfo->currentFrameX = 0;
	imageInfo->currentFramY = 0;
	AnimationIndex = 0;
	ReleaseDC(g_hWnd, hdc);

	if (imageInfo->hBitmap == NULL)
	{
		Release();
		return E_FAIL;
	}


	this->isTransparent = isTransparent;
	this->transColor = transColor;


	return S_OK;
}

void Image::Release()
{
	if (imageInfo) 
	{
		SelectObject(imageInfo->hMemDC, imageInfo->hOldBit);
		DeleteObject(imageInfo->hBitmap);
		DeleteDC(imageInfo->hMemDC);
		delete imageInfo;
		imageInfo = nullptr;
	}

}

void Image::Render(HDC hdc, int destX, int destY)
{
	if (isTransparent) //특정색이 있는지 확인
	{
		GdiTransparentBlt(
			hdc,
			destX, destY,
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			imageInfo->width,
			imageInfo->height, transColor);
		//특정 색상을 빼고 복사하는 함수
	}
	else 
	{
		BitBlt(
			hdc,//복사 목적지 DC
			0, 0, // 복사 시작 위치
			imageInfo->width,
			imageInfo->height,
			imageInfo->hMemDC,
			0, 0,
			SRCCOPY
		); //BITMAP에 있는 이미지 정보를 다른 비트맵에 복사
	}
}

void Image::Render(HDC hdc, int destX, int destY, int frameIndex)
{
	imageInfo->currentFrameX = frameIndex;

	if (isTransparent) //특정색이 있는지 확인
	{
		GdiTransparentBlt(
			hdc,				//목적지 DC
			destX, destY,		//복사 위치
			imageInfo->frameWidth,imageInfo->frameHeight, //복사 크기
			imageInfo->hMemDC, //원본 DC
			imageInfo->frameWidth* imageInfo->currentFrameX, //원본 DC 복사 위치
			imageInfo->frameHeight* imageInfo->currentFramY, //원본 DC 복사 위치
			imageInfo->frameWidth,imageInfo->frameHeight,  //복사 크기
			transColor); //제외 할 색상
		//특정 색상을 빼고 복사하는 함수
	}
	else 
	{
		BitBlt(
			hdc,
			destX, destY,
			imageInfo->frameWidth,
			imageInfo->frameHeight,
			imageInfo->hMemDC,
			imageInfo->frameWidth * imageInfo->currentFrameX, imageInfo->frameHeight * imageInfo->currentFramY,
			SRCCOPY
		);
	}
	
}

