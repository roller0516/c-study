#pragma once
#include "Singleton.h"
#define MAX_KEY_COUNT 256
using namespace std;
class KeyManager:public Singleton<KeyManager>
{
private:
	bitset<MAX_KEY_COUNT> keyup; //현재 키가 위로 올라와 있는지 확인
	bitset<MAX_KEY_COUNT> keyDown; // 현재 키가 눌려 있는지 확인
	int count;
public :
	HRESULT Init();
	void Release();
	vector<int> inputkey; // 키값을 가져옴
	vector<int> Savekey; //키 저장

	bool IsOnceKeyDown(int key);
	void VectorKey(int key); //키가 처음 눌렸는지 판단
	bool IsOnceKeyUp(int key); // 키가 눌렸다가 처음 떼어졌는지 판단
	bool IsStayKeyDown(int key); // 키가 계속 눌려있는지 판단
	bool KeyComboDown(int key);

	vector<int>GetKeyValue() 
	{
		return this->inputkey;
	}
	int GetCount() { return this->count; }
	void SetKeyDown(int key, bool down) { this->keyDown.set(key, down); }
	void SetKeyUp(int key, bool down) { this->keyup.set(key, down); }
};

