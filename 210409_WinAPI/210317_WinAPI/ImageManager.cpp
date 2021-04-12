#include "ImageManager.h"
#include "Image.h"
HRESULT ImageManager::Init()
{
	return S_OK;
}

void ImageManager::Release()
{
	map<string, Image*>::iterator iter;
	for (iter = mImageDatas.begin(); iter != mImageDatas.end(); iter++) 
	{
		iter->second->Release();
		delete iter->second;
		iter->second = nullptr;
	}
	mImageDatas.clear();

	ReleaseSingleton();
}

Image* ImageManager::AddImage(string key, const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
	Image* image = nullptr;
	//맵에 키에 해당되는 데이터가 있으면 추가생성없이 리턴
	image = FindImage(key);
	if (image)
	{
		return image;
	}

	image = new Image();
	if (FAILED(image->Init(fileName, width, height, isTransparent, transColor)))
	{
		image->Release();
		delete image;
		return nullptr;
	}

	mImageDatas.insert(make_pair(key, image));
}

Image* ImageManager::AddImage(string key, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
	Image* image = nullptr;
	//맵에 키에 해당되는 데이터가 있으면 추가생성없이 리턴
	image = FindImage(key);
	if (image)
	{
		return image;
	}

	image = new Image();
	if (FAILED(image->Init(fileName, width, height,maxFrameX,maxFrameY,isTransparent, transColor)))
	{
		image->Release();
		delete image;
		return nullptr;
	}

	mImageDatas.insert(make_pair(key, image));
}

Image* ImageManager::FindImage(string key)
{
	map<string, Image*>::iterator iter;
	iter = mImageDatas.find(key);

	if(iter == mImageDatas.end())//못 찾았다
	{
		return nullptr;
	}

	return iter->second;
}

Image* ImageManager::DeleteImage(string key)
{
	map<string, Image*>::iterator iter = mImageDatas.begin();
	iter = mImageDatas.find(key);

	if (iter == mImageDatas.end())
		return nullptr;

	(iter->second)->Release();
	delete (iter->second);
	(iter->second) = nullptr;

	mImageDatas.erase(iter);
}


