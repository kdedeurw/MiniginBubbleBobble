#pragma once
#include "SingletonRef.h"
#include <string>
#include <vector>
#include <fstream>

struct LevelTiles
{
	//id is taken from std::vector index
	const static int Width = 32;
	const static int Height = 25;
	bool Tiles[Width][Height];
};

class LevelParser final : public SingletonRef<LevelParser>
{
public:
	LevelParser();
	~LevelParser();

	void Read(const std::string& file);

	const std::vector<LevelTiles>& GetLevels() const { return m_Levels; };

private:
	std::ifstream m_Reader;

	const int m_Amount = 100;
	std::vector<LevelTiles> m_Levels;
	//blocks wide per level 32
	//blocks high per level 25
	//blocks per byte 8

	using byte = unsigned char;
	void AddLevel(std::vector<byte>& bytes);
};