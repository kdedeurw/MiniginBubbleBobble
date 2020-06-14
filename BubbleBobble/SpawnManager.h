#pragma once
#include "SingletonRef.h"
#include "Vectors.h"
#include "Types.h"

class GameObject;
class SpawnManager : public SingletonRef<SpawnManager>
{
public:
	~SpawnManager();

	//static functions?
	GameObject* CreateEnemy(EnemyType type, const Vector2& pos = Vector2{ 50.f, 50.f });
	GameObject* CreateItem(ItemType type, const Vector2& pos = Vector2{ 50.f, 50.f });

private:
	friend static SpawnManager& SingletonRef<SpawnManager>::GetInstance();
	SpawnManager() = default;

	const float m_Size = 16.f;
};
