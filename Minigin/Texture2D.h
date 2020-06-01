#pragma once
#include "Texture.h"
#include "Math.h"

class Texture2D : public Texture
{
public:
	explicit Texture2D(SDL_Texture* pTexture);
	virtual ~Texture2D();
	Texture2D(const Texture2D &) = delete;
	Texture2D(Texture2D &&) = delete;
	Texture2D & operator= (const Texture2D &) = delete;
	Texture2D & operator= (const Texture2D &&) = delete;

	const Vector2& GetDimensions() const;

	bool Initialize();

private:
	Vector2 m_Dimensions;
};