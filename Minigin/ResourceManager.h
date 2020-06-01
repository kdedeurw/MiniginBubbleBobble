#pragma once
#include "SingletonRef.h"
#include <map>

class Texture2D;
class Font;
class ResourceManager final : public SingletonRef<ResourceManager>
{
public:
	~ResourceManager();

	void Init(const std::string& data);
	Texture2D* LoadTexture(const std::string& file);
	Font* LoadFont(const std::string& file, unsigned int size);

private:
	friend class SingletonRef<ResourceManager>;
	ResourceManager() = default;
	std::string m_DataPath;

	std::map<std::string, Texture2D*> m_Textures;
	std::map<std::string, Font*> m_Fonts;
};