#pragma once
#include "Component.h"
//TODO: remove
#include "LevelParser.h"
#include "Vectors.h"

class Texture2D;
class RigidBody;
class Level : public Component
{
public:
	//TODO: make singleton instead of component
	Level();
	~Level();

	virtual void Initialize() override;
	virtual void Render() const override;
	virtual void Update() override;

	void SetLevel(const std::vector<LevelTiles>* pLevels);

private:
	Texture2D* m_pTexture;
	int m_LevelIndex;
	const float m_TileSize = 8.f;
	const std::vector<LevelTiles>* m_pLevels;
	std::vector<RigidBody> m_Collisions;
};