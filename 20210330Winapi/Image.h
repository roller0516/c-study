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
	//�� ��Ʈ�� �̹����� ����� �Լ�
	HRESULT Init(int width, int height);
	//���Ϸκ��� �̹����� �ε� �ϴ� �Լ�
	HRESULT Init(const char* fileName, int width, int height);
	void Release();
	void Render(HDC hdc);
};

