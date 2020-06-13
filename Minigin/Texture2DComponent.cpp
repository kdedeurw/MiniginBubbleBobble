#include "MiniginPCH.h"
#include "Texture2DComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Math.h"

Texture2DComponent::Texture2DComponent()
	: m_pTexture{}
{}

Texture2DComponent::~Texture2DComponent()
{
	m_pTexture = nullptr;
}

void Texture2DComponent::Initialize()
{
	if (!m_pTexture->InitializeTexture())
		throw std::exception("Texture2DComponent::Initialize > invalid texture");
}

void Texture2DComponent::Render() const
{
	const Vector2& pos = m_pGameObject->GetFinalPos();
	const Vector2& scale = m_pGameObject->GetTransform().GetScale();
	const Vector4& dstRec = m_pTexture->GetDestRect();
	const Vector4& srcRect = m_pTexture->GetSourceRect();
	Renderer::GetInstance().RenderTexture(m_pTexture->GetSDLTexture(), 
		(pos.x + dstRec.x) - (dstRec.z / 2 * scale.x), //x
		(pos.y + dstRec.y) + (dstRec.w / 2 * scale.y), //y, swapped because origin of XY is down left
		dstRec.z * scale.x, dstRec.w * scale.y, //scale
		srcRect.x, srcRect.y, srcRect.z, srcRect.w, //srcRct
		m_pGameObject->GetTransform().GetRotation()); //rot
}

void Texture2DComponent::Update()
{}

void Texture2DComponent::SetTexture(SDL_Texture* pTexture)
{
	//TODO: remove/unsafe
	if (!m_pTexture)
		m_pTexture = GlobalMemoryPools::GetInstance().CreateTexture2D(pTexture);
	else
		m_pTexture->SetTexture(pTexture);
	m_pTexture->InitializeTexture();
}

void Texture2DComponent::SetTexture(const std::string& fileAsset)
{
	if (!m_pTexture)
		m_pTexture = ResourceManager::GetInstance().LoadTexture(fileAsset);
	else
		m_pTexture->SetTexture(fileAsset);
	m_pTexture->InitializeTexture();
}