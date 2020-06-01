#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

Texture2D::Texture2D(SDL_Texture* pTexture)
	: Texture{ pTexture }
	//, m_Dimensions{}
{}

Texture2D::~Texture2D()
{}

const Vector2& Texture2D::GetDimensions() const
{
	return m_Dimensions;
}

bool Texture2D::Initialize()
{
	int width, height;
	if (!SDL_QueryTexture(m_pTexture, nullptr, nullptr, &width, &height))
	{
		m_Dimensions.x = (float)width;
		m_Dimensions.y = (float)height;
		return true;
	}
	return false;
}