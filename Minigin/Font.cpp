#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "Font.h"

Font::Font(const std::string& fullPath, unsigned int size)
	: m_pFont{ TTF_OpenFont(fullPath.c_str(), std::move(size)) }
	, m_Size{ std::move(size) }
{
	if (!m_pFont)
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
}

Font::~Font()
{
	//TTF_CloseFont(m_pFont);
	//this is being managed by the >ResourceManager<(/GlobalMemoryPools)
	m_pFont = nullptr;
}

TTF_Font* Font::GetFont() const
{
	return m_pFont;
}

const unsigned int Font::GetSize() const
{
	return m_Size;
}