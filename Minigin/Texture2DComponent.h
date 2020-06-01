#pragma once
#include "Component.h"
#include "Texture2D.h"

class Texture2DComponent : public Component
{
public:
	Texture2DComponent();
	~Texture2DComponent();

	virtual void Initialize() override;
	virtual void Render(Transform* pParentTrans = nullptr) const override;
	virtual void Update() override;

	//easily switch textures
	void SetTexture(Texture2D* pTexture);
	//load in new texture (new textures take time to load)
	void SetTexture(const std::string& fileAsset);
	//the rectangle from where the renderer should sample the texture from (entire texture dimensions by default)
	//x being X sample offset, y being Y sample offset, z being Width (default texture width), w being Height (default texture height)
	//aka Sample Destination quad on texture
	void SetSourceRect(Vector4 srcRect);
	//the rectangle in 2D world space where the renderer should draw the texture (entire texture dimensions by default)
	//x being X pos offset, y being Y pos offset, z being Width (default source width), w being Height (default source height)
	//aka Render Destination quad in world space
	void SetDestRect(Vector4 dstRect);

	Vector4& GetSourceRect();
	Vector4& GetDestRect();

protected:
	Texture2D* m_pTexture;
	Vector4 m_SourceRect;
	Vector4 m_DestRect;

	void InitializeTexture();
};