#include "config.h"
#include "KeyManager.h"


HRESULT KeyManager::Init()
{

    keyup.reset();
    keyDown.reset();
   /* for(int i = 0 ; i < MAX_KEY_COUNT; i++)
    {
        keyup[i] = true;
        keyDown[i] = false;
    }*/
	count = 0;
    return S_OK;
}

void KeyManager::Release()
{
    ReleaseSingleton();
}

bool KeyManager::IsOnceKeyDown(int key)
{
    /*
    *  GetAsyncKeyState(VK_...) 
    * 
    *  함수 호출 시점에 가상키(VK_...)가 어떤 상태인지 확인
    *  1. 0x0000 (16진수) -> 이전 프레임에 누른적이 없고 호출시점에도 눌려있지 않음. 0이랑같음 (아무것도 아닌 상태)
    *  2. 0x0001 -> 이전 프레임에 누른적이 있고 호출시점에는 눌려있지 않음.(눌렀다 뗐음)
    *  3. 0x8000 -> 이전 프레임에 누른적이 없고 호출시점에는 눌려있는 상태. (한번 누른 상태)
    *  4. 0x8001 -> 이전 프레임에 누른적이 있고 호출시점에도 눌려있는 상태. (계속 누르고있는 상태)
    */
    if (GetAsyncKeyState(key) & 0x8000) //bit 연산  |
    {
        if (keyDown[key] == false) 
        {
            keyDown[key] = true;
			count++;
			inputkey.push_back(key);
            return true;
        }
    }
    else 
    {
        keyDown[key] = false;
    }
    return false;
}
void KeyManager::VectorKey(int key)
{
	/*
	*  GetAsyncKeyState(VK_...)
	*
	*  함수 호출 시점에 가상키(VK_...)가 어떤 상태인지 확인
	*  1. 0x0000 (16진수) -> 이전 프레임에 누른적이 없고 호출시점에도 눌려있지 않음. 0이랑같음 (아무것도 아닌 상태)
	*  2. 0x0001 -> 이전 프레임에 누른적이 있고 호출시점에는 눌려있지 않음.(눌렀다 뗐음)
	*  3. 0x8000 -> 이전 프레임에 누른적이 없고 호출시점에는 눌려있는 상태. (한번 누른 상태)
	*  4. 0x8001 -> 이전 프레임에 누른적이 있고 호출시점에도 눌려있는 상태. (계속 누르고있는 상태)
	*/
	for (int i = 0; i < this->count; i++) 
	{
		inputkey.push_back(key);
	}
}

bool KeyManager::IsOnceKeyUp(int key)
{
    if (GetAsyncKeyState(key) & 0x8000)
    {
        keyup[key] = false;
        return false;
    }
    else 
    {
        if (keyup[key] == false) 
        {
            keyup[key] = true;
            return true;
        }
    }
    return false;
}

bool KeyManager::IsStayKeyDown(int key)
{
    if (GetAsyncKeyState(key) & 0x8000) 
    {
        return true;
    }
    return false;
}

bool KeyManager::KeyComboDown(int key)
{
	



	return false;
}
