#include "MiniginPCH.h"
#include "Level.h"
#include "Texture2D.h"
#include "GlobalInput.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "RigidBody.h"

Level::Level()
	: m_pLevels{}
	, m_LevelIndex{}
	, m_pTexture{}
	, m_Collisions{}
{}

Level::~Level()
{
	m_pTexture = nullptr;
	m_pLevels = nullptr;
}

void Level::Initialize()
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture("Levels/LevelBlocks.png");
	m_pTexture->InitializeTexture();

	Vector4& dstRec = m_pTexture->GetDestRect();
	Vector4& srcRect = m_pTexture->GetSourceRect();
	srcRect.z = srcRect.w = m_TileSize;
	dstRec.z = dstRec.w = m_TileSize;
}

void Level::Render() const
{
	const Vector2& pos = m_pGameObject->GetFinalPos();
	const Vector2& scale = m_pGameObject->GetTransform().GetScale();
	const Vector4& srcRect = m_pTexture->GetSourceRect();
	for (int x{}; x < LevelTiles::Width; ++x)
	{
		for (int y{}; y < LevelTiles::Height; ++y)
		{
			if (m_pLevels->at(m_LevelIndex).Tiles[x][y])
			{
				const Vector4 dstRec{ x * 8.f * 2, y * 8.f * 2, srcRect.z, srcRect.w };
				Renderer::GetInstance().RenderTexture(m_pTexture->GetSDLTexture(),
					(pos.x + dstRec.x) - (dstRec.z / 2 * scale.x),
					(pos.y + dstRec.y) + (dstRec.w / 2 * scale.y),
					dstRec.z * scale.x, dstRec.w * scale.y,
					srcRect.x, srcRect.y, srcRect.z, srcRect.w);

			}
		}
	}

	for (const RigidBody& rb : m_Collisions)
	{
		rb.DrawDebug();
	}
}

void Level::Update()
{
	KeyboardMouseListener& kbml = GlobalInput::GetInstance().KeyboardMouseListener;

	if (kbml.IsScrollWheelMove(ScrollWheel::Up))
		++m_LevelIndex;
	else if (kbml.IsScrollWheelMove(ScrollWheel::Down))
		--m_LevelIndex;

	if (m_LevelIndex < 0 || m_LevelIndex >= (int)m_pLevels->size())
		m_LevelIndex = 0;

	Vector4& srcRect = m_pTexture->GetSourceRect();
	srcRect.x = ((m_LevelIndex - 1) % 10) * m_TileSize;
	srcRect.x = ((m_LevelIndex - 1) / 10) * m_TileSize;

	//TODO: collision
	for (RigidBody& rb : m_Collisions)
		rb.DestroyBody();
	m_Collisions.clear();
	const Vector2& pos = m_pGameObject->GetTransform().GetPosition();
	for (int x{}; x < LevelTiles::Width; ++x)
	{
		for (int y{}; y < LevelTiles::Height; ++y)
		{
			if (m_pLevels->at(m_LevelIndex).Tiles[x][y])
			{
				RigidBody rb{};
				rb.CreateBox(Vector2{ pos.x + x * 16.f, pos.x + y * 16.f }, 0.f, Vector2{ 8.f, 8.f });
				m_Collisions.push_back(rb);
			}
		}
	}
}

void Level::SetLevel(const std::vector<LevelTiles>* pLevels)
{
	m_pLevels = pLevels;
}