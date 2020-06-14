#pragma once
#include "Component.h"
#include "Subject.h"
#include "Vectors.h"
#include "Structs.h"

class Texture2D;
class RigidBody;
class Level : public Component, public Subject
{
public:
	//TODO: make singleton instead of component
	Level();
	~Level();

	virtual void Initialize() override;
	virtual void Render() const override;
	virtual void Update() override;

	void SetLevels(const std::vector<LevelTiles>* pLevels);
	void SetEnemyData(const std::vector<EnemyData>* pEnemyData);
	void NextLevel();

private:
	Texture2D* m_pTexture;
	int m_LevelIndex;
	const float m_TileSize = 8.f;
	const std::vector<LevelTiles>* m_pLevels;
	const std::vector<EnemyData>* m_pEnemies;
	std::vector<RigidBody> m_Collisions;
};