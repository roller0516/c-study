#pragma once
#include "config.h"
class Image 
{
public :
	enum  IMAGE_LOAD_KIND
	{
		RESOURCE,	//������Ʈ ��ü�� ���� ��ų �̹���
		FILE,		// �ܺο��� �ε��� �̹���
		EMPTY,		//��ü ���� �̹��� �����ս�, ��������,
		END  
	};

	typedef struct tageImageInfo 
	{
		DWORD resID;		//���ҽ��� ������ ID
		HDC hMemDC;			//�׸��⸦ �ְ��ϴ� �ڵ�
		HBITMAP hBitmap;	//�̹��� ����
		HBITMAP hOldBit;	//���� �̹��� ����
		int width;			//�̹��� ���� ũ��
		int height;			//�̹��� ���� ũ��
		BYTE loadType;		//�ε�Ÿ��
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currentFrameX;
		int currentFramY;
		tageImageInfo() 
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_KIND::EMPTY;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currentFrameX = 0;
			currentFramY = 0;
		}

	}IMAGE_INFO,*LPIMAGE_INFO;
private:
	IMAGE_INFO* imageInfo;
	bool isTransparent;
	COLORREF transColor;
	int Count;
	int AnimationIndex;
public:
	//�� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);
	//���Ϸκ��� �̹����� �ε� �ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height,bool isTransparent = FALSE,COLORREF transColor = FALSE);
	HRESULT Init(const char* fileName, int width, int height,int maxFrameX,int maxFrameY ,bool isTransparent = FALSE, COLORREF transColor = FALSE);
	void Release();
	void Render(HDC hdc,int destX = 0, int destY =0);
	void Render(HDC hdc, int destX , int destY, int frameIndex);
	inline void SetAnimation(int Count) { this->Count = Count; }
	HDC GetMemDC() 
	{
		if (this->imageInfo)
			return this->imageInfo->hMemDC;
		return NULL;
	}
};

