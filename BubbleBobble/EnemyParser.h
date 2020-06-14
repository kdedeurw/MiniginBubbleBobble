#pragma once
#include "BinaryReader.h"
#include "SingletonRef.h"
#include "Types.h"
#include "Structs.h"

class EnemyParser : public BinaryReader, public SingletonRef<EnemyParser>
{
public:
	EnemyParser();
	~EnemyParser();

	void Parse(const std::string& file);

	const std::vector<EnemyData>& GetData() const { return m_Enemies; };

private:
	std::vector<EnemyData> m_Enemies;

	using byte = unsigned char;
	void AddEnemies(std::vector<byte>& bytes);
	EnemyData& AddEnemy(byte byte1, byte byte2, byte byte3);
	EnemyType DetectEnemyType(byte byte);
	int ExtractBitMask(byte b);
	float ExtractDelay(byte b);

	const float m_TimeDelay = 0.017f;
};