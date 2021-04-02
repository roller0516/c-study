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
    *  �Լ� ȣ�� ������ ����Ű(VK_...)�� � �������� Ȯ��
    *  1. 0x0000 (16����) -> ���� �����ӿ� �������� ���� ȣ��������� �������� ����. 0�̶����� (�ƹ��͵� �ƴ� ����)
    *  2. 0x0001 -> ���� �����ӿ� �������� �ְ� ȣ��������� �������� ����.(������ ����)
    *  3. 0x8000 -> ���� �����ӿ� �������� ���� ȣ��������� �����ִ� ����. (�ѹ� ���� ����)
    *  4. 0x8001 -> ���� �����ӿ� �������� �ְ� ȣ��������� �����ִ� ����. (��� �������ִ� ����)
    */
    if (GetAsyncKeyState(key) & 0x8000) //bit ����  |
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
	*  �Լ� ȣ�� ������ ����Ű(VK_...)�� � �������� Ȯ��
	*  1. 0x0000 (16����) -> ���� �����ӿ� �������� ���� ȣ��������� �������� ����. 0�̶����� (�ƹ��͵� �ƴ� ����)
	*  2. 0x0001 -> ���� �����ӿ� �������� �ְ� ȣ��������� �������� ����.(������ ����)
	*  3. 0x8000 -> ���� �����ӿ� �������� ���� ȣ��������� �����ִ� ����. (�ѹ� ���� ����)
	*  4. 0x8001 -> ���� �����ӿ� �������� �ְ� ȣ��������� �����ִ� ����. (��� �������ִ� ����)
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
