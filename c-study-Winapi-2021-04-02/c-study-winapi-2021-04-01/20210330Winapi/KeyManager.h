#pragma once
#include "Singleton.h"
#define MAX_KEY_COUNT 256
using namespace std;
class KeyManager:public Singleton<KeyManager>
{
private:
	bitset<MAX_KEY_COUNT> keyup; //���� Ű�� ���� �ö�� �ִ��� Ȯ��
	bitset<MAX_KEY_COUNT> keyDown; // ���� Ű�� ���� �ִ��� Ȯ��
	int count;
public :
	HRESULT Init();
	void Release();
	vector<int> inputkey; // Ű���� ������
	vector<int> Savekey; //Ű ����

	bool IsOnceKeyDown(int key);
	void VectorKey(int key); //Ű�� ó�� ���ȴ��� �Ǵ�
	bool IsOnceKeyUp(int key); // Ű�� ���ȴٰ� ó�� ���������� �Ǵ�
	bool IsStayKeyDown(int key); // Ű�� ��� �����ִ��� �Ǵ�
	bool KeyComboDown(int key);

	vector<int>GetKeyValue() 
	{
		return this->inputkey;
	}
	int GetCount() { return this->count; }
	void SetKeyDown(int key, bool down) { this->keyDown.set(key, down); }
	void SetKeyUp(int key, bool down) { this->keyup.set(key, down); }
};

