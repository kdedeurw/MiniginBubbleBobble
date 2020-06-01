#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameState.h"
#include "MemoryAllocator.h"

SceneManager::SceneManager()
	: m_pScenes{}
{}

SceneManager::~SceneManager()
{
	for (Scene* pScene : m_pScenes)
	{
		delete pScene;
	}
	m_pScenes.clear();
}

void SceneManager::Update()
{
	for(Scene* pScene : m_pScenes)
	{
		pScene->Update();
	}
}

void SceneManager::Render() const
{
	for (const Scene* pScene : m_pScenes)
	{
		pScene->Render();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	Scene* pScene = GlobalMemoryPools::GetInstance().CreateScene(name.c_str());
	m_pScenes.push_back(pScene);
	return *pScene;
}
