#pragma once
#include "GlobalMemoryPools.h"

class SceneObject;
class GameObject;
class TextObject;
class Scene
{
public:
	virtual ~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	void AddObject(SceneObject* pObject);

	void Initialize();
	void Update();
	void Render() const;

	bool operator==(const Scene& other);

protected:
	//friend Scene* GlobalMemoryPools::CreateScene(const std::string& name);
	friend class GlobalMemoryPools;
	explicit Scene(std::string name);

	friend class SceneManager; //why not
	std::string m_Name;
	std::vector<SceneObject*> m_pObjects;

private:
	static unsigned int m_IdCounter;
};