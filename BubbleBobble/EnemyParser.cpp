#include "MiniginPCH.h"
#include "EnemyParser.h"
#include <bitset>

EnemyParser::EnemyParser()
    : m_Enemies{}
{
}

EnemyParser::~EnemyParser()
{
}

void EnemyParser::Parse(const std::string& file)
{
    OpenFile("../Data/Levels/" + file);

    std::vector<byte> bytes{};
    //read through entire file
    while (IsGood())
    {
        bytes.push_back(Read<byte>());
    }
    AddEnemies(bytes);
}

void EnemyParser::AddEnemies(std::vector<byte>& bytes)
{
    int lvlId{};
    EnemyData enemy{};
    const int size{ (int)bytes.size() - 1 };
    //last 3 bytes seem to be 2 empty ones and 1 garbage byte, 
    //so we filter the 2 empty ones (levelId from 0 to 99) and discard the last garbage one (secret)
    int i{};
    while (i < size)
    {
        if (bytes[i] == 0) //end of level
        {
            ++lvlId;
            ++i;
            continue;
        }

        AddEnemy(bytes[i], bytes[i + 1], bytes[i + 2]).levelId = lvlId;
        i += 3;
    }
}

EnemyData& EnemyParser::AddEnemy(byte byte1, byte byte2, byte byte3)
{
    EnemyData enemy{};
    enemy.type = DetectEnemyType(byte1);
    enemy.x = ExtractBitMask(byte1);
    enemy.y = LevelTiles::Rows - ExtractBitMask(byte2);//enemies drop to tile at height y (top == 0 => bottom == 0)
    enemy.delay = ExtractDelay(byte3) * m_TimeDelay;
    m_Enemies.push_back(enemy);
    return m_Enemies.back();
}

EnemyType EnemyParser::DetectEnemyType(byte b)
{
    //access individual bits in byte
    //bool test = (b >> NrBit) & 1;

    std::bitset<8> bits{ b };

    byte byte{};
    //set first 3 bits
    byte |= bits[0] << 0;
    byte |= bits[1] << 1;
    byte |= bits[2] << 2;

    //Byte 1 Mask 0b00000111 = enemy type
    //000 = Zen chan
    //110 = Mighta
    //100 = Monsta
    //011 = Pulpul
    //010 = Banebou
    //001 = Hidegons
    //101 = Drunk
    //111 = Invader

    if (byte == 0)
        return EnemyType::ZenChan;
    if (byte == 6)
        return EnemyType::Maita;
    if (byte == 4)
        return EnemyType::Monsta;
    if (byte == 3)
        return EnemyType::Pulpul;
    if (byte == 2)
        return EnemyType::Banebou;
    if (byte == 1)
        return EnemyType::Hidegons;
    if (byte == 5)
        return EnemyType::Drunk;
    else //(byte & 0b00000111)
        return EnemyType::Invader;

    //if (byte & 0b00000000)
    //    return EnemyType::ZenChan;
    //if (byte & 0b00000110)
    //    return EnemyType::Maita;
    //if (byte & 0b00000100)
    //    return EnemyType::Monsta;
    //if (byte & 0b00000011)
    //    return EnemyType::Pulpul;
    //if (byte & 0b00000010)
    //    return EnemyType::Banebou;
    //if (byte & 0b00000001)
    //    return EnemyType::Hidegons;
    //if (byte & 0b00000101)
    //    return EnemyType::Drunk;
    //if (byte & 0b00000111)
    //    return EnemyType::Invader;
}

int EnemyParser::ExtractBitMask(byte b)
{
    //access individual bits in byte
    //bool test = (b >> NrBit) & 1;

    std::bitset<8> ok{ b };

    byte byte{};
    //set last 5 bits
    byte |= ok[3] << 3;
    byte |= ok[4] << 4;
    byte |= ok[5] << 5;
    byte |= ok[6] << 6;
    byte |= ok[7] << 7;

    byte >>= 3;

    return (int)byte;
}

float EnemyParser::ExtractDelay(byte b)
{
    //access individual bits in byte
    //bool test = (b >> NrBit) & 1;

    std::bitset<8> ok{ b };

    byte byte{};
    //set first 6 bits
    byte |= ok[0] << 0;
    byte |= ok[1] << 1;
    byte |= ok[2] << 2;
    byte |= ok[3] << 3;
    byte |= ok[4] << 4;
    byte |= ok[5] << 5;

    byte <<= 1;

    return (float)byte;
}
