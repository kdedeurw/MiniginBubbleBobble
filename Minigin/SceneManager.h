#pragma once
#include "SingletonRef.h"

class Scene;
class SceneManager final : public SingletonRef<SceneManager>
{
public:
	~SceneManager();

	void Update();
	void Render() const;

	Scene& CreateScene(const std::string& name);

private:
	friend static SceneManager& SingletonRef<SceneManager>::GetInstance();
	SceneManager();

	std::vector<Scene*> m_pScenes;
};