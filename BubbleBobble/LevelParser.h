#pragma once
#include "BinaryReader.h"
#include "SingletonRef.h"
#include "Structs.h"

class LevelParser final : public BinaryReader, public SingletonRef<LevelParser>
{
public:
	LevelParser();
	~LevelParser();

	void Parse(const std::string& file);

	const std::vector<LevelTiles>& GetLevels() const { return m_Levels; };

private:
	const int m_Amount = 100;
	std::vector<LevelTiles> m_Levels;
	//blocks wide per level 32
	//blocks high per level 25
	//blocks per byte 8

	void AddLevel(std::vector<byte>& bytes);
};