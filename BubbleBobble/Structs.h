#pragma once
#include "Types.h"

struct LevelTiles
{
	//id is taken from std::vector index
	const static int Columns = 32;
	const static int Rows = 25;
	bool Tiles[Columns][Rows];
};

struct EnemyData
{
	int x;
	int y;
	EnemyType type;
	float delay;
	int levelId;
};