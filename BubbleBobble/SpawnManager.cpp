#include "MiniginPCH.h"
#include "SpawnManager.h"
#include "GlobalMemoryPools.h"
#include "GameObject.h"
#include "Texture2DComponent.h"
#include "SpriteComponent.h"
#include "ItemPickup.h"
#include "PhysicsComponent.h"
#include "ColliderMasks.h"

SpawnManager::~SpawnManager()
{}

GameObject* SpawnManager::CreateEnemy(EnemyType type, const Vector2& pos)
{
	 GameObject* pGo = GlobalMemoryPools::GetInstance().CreateGameObject();
	 Transform& trans = pGo->GetTransform();
	 trans.SetPosition(pos);

	 SpriteComponent* pSprites = GlobalMemoryPools::GetInstance().CreateComponent<SpriteComponent>();
	 pGo->AddComponent(pSprites);
	 pSprites->SetTexture("EnemySprites.png");
	 pSprites->SetMaxFrames(4);
	 pSprites->SetTickRate(0.25f);
	 pSprites->SetSizes(Vector2{ m_Size, m_Size });

	 Vector4& srcRect = pSprites->GetSourceRect();
	 //Vector4& dstRect = pSprites->GetDestRect();
	 //srcRect.z = srcRect.w = dstRect.z = dstRect.w = m_Size;
	 srcRect.y = (int)type * m_Size;

	 PhysicsComponent* pPhys = GlobalMemoryPools::GetInstance().CreateComponent<PhysicsComponent>();
	 pGo->AddComponent(pPhys);
	 pPhys->CreateBox(pos, 0.f, Vector2{ 16.f, 16.f }, true, ColliderMask::PLAYER, ColliderMask::ITEM, PhysicsComponent::Type::Dynamic);

	 //TODO: add enemy AI component
	 switch (type)
	 {
	 case EnemyType::ZenChan:
		 break;
	 case EnemyType::Hidegons:
		 break;
	 case EnemyType::Banebou:
		 break;
	 case EnemyType::Pulpul:
		 break;
	 case EnemyType::Monsta:
		 break;
	 case EnemyType::Drunk:
		 break;
	 case EnemyType::Maita:
		 break;
	 case EnemyType::Invader:
		 break;
	 default:
		 break;
	 }

	 return pGo;
}

GameObject* SpawnManager::CreateItem(ItemType type, const Vector2& pos)
{
	GameObject* pGo = GlobalMemoryPools::GetInstance().CreateGameObject();
	Transform& trans = pGo->GetTransform();
	trans.SetPosition(pos);

	Texture2DComponent* pTex = GlobalMemoryPools::GetInstance().CreateComponent<Texture2DComponent>();
	pGo->AddComponent(pTex);
	pTex->SetTexture("Itemsprites.png");

	Vector4& srcRect = pTex->GetSourceRect();
	Vector4& dstRect = pTex->GetDestRect();
	srcRect.z = srcRect.w = dstRect.z = dstRect.w = m_Size;
	srcRect.y = (int)type * m_Size;

	PhysicsComponent* pPhys = GlobalMemoryPools::GetInstance().CreateComponent<PhysicsComponent>();
	pGo->AddComponent(pPhys);
	pPhys->CreateBox(pos, 0.f, Vector2{ 16.f, 16.f }, true, ColliderMask::PLAYER, ColliderMask::ITEM, PhysicsComponent::Type::Kinematic);

	ItemPickup* pItem = GlobalMemoryPools::GetInstance().CreateComponent<ItemPickup>();
	pGo->AddComponent(pItem);
	pItem->SetScore(type);

	return pGo;
}
