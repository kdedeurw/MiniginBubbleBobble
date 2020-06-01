#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "GlobalMemoryPools.h"
#include "Texture2D.h"
#include "Font.h"

ResourceManager::~ResourceManager()
{
	////delete SDL_Object*'s
	//for (auto& it : m_Textures)
	//{
	//	SDL_DestroyTexture(it.second->GetSDLTexture());
	//}
	//for (auto& it : m_Fonts)
	//{
	//	TTF_CloseFont(it.second->GetFont());
	//}
}

void ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

Texture2D* ResourceManager::LoadTexture(const std::string& file)
{
	//search whether the texture already exists
	const auto it = m_Textures.find(file);
	if (it != m_Textures.end())
		return it->second;

	//if not, create a new texture and store it
	const std::string fullPath = m_DataPath + file;
	SDL_Texture* texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return m_Textures[file] = GlobalMemoryPools::GetInstance().CreateTexture2D(texture);
	//can either manage own memory (copying pointers during init of a scene) or have a table of textures (like the above)
}

Font* ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	const auto it = m_Fonts.find(file);
	//if font exists
	if (it != m_Fonts.end())
	{
		//with same size
		if (size == it->second->GetSize())
			return it->second;
		//or not
		else
		{
			//search for unique font
			const std::string newName = file + std::to_string(size);
			const auto itSize = m_Fonts.find(newName);
			if (itSize != m_Fonts.end())
				return it->second;
			//or simply create new one
			return m_Fonts[newName] = GlobalMemoryPools::GetInstance().CreateOwnFont(m_DataPath + file, size);
		}
	}
	//if not, create new font
	return m_Fonts[file] = GlobalMemoryPools::GetInstance().CreateOwnFont(m_DataPath + file, size);
}