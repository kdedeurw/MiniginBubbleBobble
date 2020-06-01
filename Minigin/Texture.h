#pragma once
#include <SDL.h>

struct SDL_Texture;
class Texture
{
public:
	explicit Texture(SDL_Texture* pTexture)
		: m_pTexture{ pTexture }
	{}
	virtual ~Texture() 
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	};
	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator= (const Texture&) = delete;
	Texture& operator= (const Texture&&) = delete;

	SDL_Texture* GetSDLTexture() const { return m_pTexture; };

protected:
	SDL_Texture* m_pTexture;
};

