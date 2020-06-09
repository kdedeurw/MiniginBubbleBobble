#include "MiniginPCH.h"
#include "Texture2DComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Math.h"

Texture2DComponent::Texture2DComponent()
	: m_pTexture{}
	//, m_SourceRect{}
	//, m_DestRect{}
{}

Texture2DComponent::~Texture2DComponent()
{
	m_pTexture = nullptr;
}

void Texture2DComponent::Initialize()
{}

void Texture2DComponent::Render() const
{
	const Vector2 pos = m_pGameObject->GetFinalPos();

	const Vector2& scale{ m_pGameObject->GetTransform().GetScale() };
	Renderer::GetInstance().RenderTexture(m_pTexture->GetSDLTexture(), 
		(pos.x + m_DestRect.x) - (m_DestRect.z / 2 * scale.x), //x
		(pos.y + m_DestRect.y) + (m_DestRect.w / 2 * scale.y), //y, swapped because origin of XY is down left
		m_DestRect.z * scale.x, m_DestRect.w * scale.y, //scale
		m_SourceRect.x, m_SourceRect.y, m_SourceRect.z, m_SourceRect.w, //srcRct
		m_pGameObject->GetTransform().GetRotation()); //rot
}

void Texture2DComponent::Update()
{
}

void Texture2DComponent::SetTexture(Texture2D* pTexture)
{
	m_pTexture = pTexture;
	InitializeTexture();
}

void Texture2DComponent::SetTexture(const std::string& fileAsset)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileAsset);
	InitializeTexture();
}

void Texture2DComponent::SetSourceRect(Vector4 srcRect)
{
	m_SourceRect = std::move(srcRect);//std::move accepts rvalue, so we move copied srcRect in m_SourceRect
}

void Texture2DComponent::SetDestRect(Vector4 dstRect)
{
	m_DestRect = std::move(dstRect);//std::move accepts rvalue, so we move copied srcRect in m_DestRect
}

void Texture2DComponent::InitializeTexture()
{
	if (!m_pTexture->Initialize())
		throw std::exception("Invalid texture for Texture2DComponent : unable to initialize");
	const Vector2& dim{ m_pTexture->GetDimensions() };
	SetSourceRect(Vector4{ 0.f, 0.f, dim.x, dim.y });
	SetDestRect(Vector4{ 0.f, 0.f, dim.x, dim.y });
}

Vector4& Texture2DComponent::GetSourceRect()
{
	return m_SourceRect;
}

Vector4& Texture2DComponent::GetDestRect()
{
	return m_DestRect;
}