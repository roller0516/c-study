#pragma once
#include "Singleton.h"

class GameNode;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<string, GameNode*> mSceneData;
public:
	static GameNode* currentScene;
	static GameNode* loadingScene;
	static GameNode* readyScene;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	GameNode* AddScene(string Key, GameNode* scene);
	HRESULT ChangeScene(string key);
};

