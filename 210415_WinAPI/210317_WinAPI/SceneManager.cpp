#include "config.h"
#include "GameNode.h"

GameNode* SceneManager::currentScene = nullptr;
GameNode* SceneManager::loadingScene = nullptr;
GameNode* SceneManager::readyScene = nullptr;

HRESULT SceneManager::Init()
{
    return S_OK;
}

void SceneManager::Release()
{
    map<string, GameNode*>::iterator it;

    for (it = mSceneData.begin(); it != mSceneData.end(); it++) 
    {
        if (it->second)
            SAFE_RELEASE(it->second);
    }
    mSceneData.clear();
        
    ReleaseSingleton();
}

void SceneManager::Update()
{
    if (currentScene)
        currentScene->Update();
}

void SceneManager::Render(HDC hdc)
{
    if (currentScene)
        currentScene->Render(hdc);
}

GameNode* SceneManager::AddScene(string Key, GameNode* scene)
{
    if (scene == nullptr)
        return nullptr;

    map<string, GameNode*>::iterator it = mSceneData.find(Key);
    if (it != mSceneData.end()) // Ã£À½
    {
        return it->second;
    }
       
    mSceneData.insert(make_pair(Key,scene));

    return scene;
}

HRESULT SceneManager::ChangeScene(string key)
{
    map<string, GameNode*>::iterator it = mSceneData.find(key);
    if (it == mSceneData.end()) // ¸øÃ£À½
        return E_FAIL;

    if(it->second == currentScene)
        return S_OK;

    if (SUCCEEDED(it->second->Init()))
    {
        //ÇöÀç ¾À -> Å¸ÀÌÆ² ¾À
        //¹Ù²Ù°í ½ÍÀº ¾À -> ¹èÆ² ¾À

        if (currentScene) 
        {
            currentScene->Release();
        }
        currentScene = it->second;

        return S_OK;
    }

    return E_FAIL;
}
