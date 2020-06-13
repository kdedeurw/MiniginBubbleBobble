#include "MiniginPCH.h"
#include "LevelParser.h"

LevelParser::LevelParser()
    : m_Reader{}
    , m_Levels{}
{}

LevelParser::~LevelParser()
{
    m_Reader.close();
    m_Levels.clear();
}

void LevelParser::Read(const std::string& file)
{
	m_Reader.open("../Data/Levels/" + file, std::ios::in | std::ios::binary);

    if (!m_Reader.is_open())
        return;

    for (int level{}; level < m_Amount; ++level)
    {
        std::vector<byte> bytes{};
        //A line is made up of 4 bytes
        //12345678 12345678 12345678 12345678 for 1 line do this times 25 for a level
        for (int l{}; l < 25 * 4; ++l)
        {
                if (!m_Reader.good())
                    break;
                //read in current line
                byte b{};
                m_Reader.read((char*)&b, sizeof(byte));
                //store line (25 per level)
                bytes.push_back(b);
        }
        //create level from 25 * 4 bytes
        //std::reverse(bytes.begin(), bytes.end());//this would reverse the horizontal layout
        AddLevel(bytes);
    }
}

void LevelParser::AddLevel(std::vector<byte>& bytes)
{
    LevelTiles level{};
    const int size{ (int)bytes.size() };//100
    int idY{ LevelTiles::Height - 1 };//reverse Y, X stays the same (flip level vertically, correct side up)
    int b{};
    while (b < size)
    {
        for (int x{}; x < 4; ++x)
        {
            const byte& byte = bytes[b];
            const int idX{ x * 8 };
            level.Tiles[0 + idX][idY] = byte & 0b10000000;//this block is a tile
            level.Tiles[1 + idX][idY] = byte & 0b01000000;
            level.Tiles[2 + idX][idY] = byte & 0b00100000;
            level.Tiles[3 + idX][idY] = byte & 0b00010000;
            level.Tiles[4 + idX][idY] = byte & 0b00001000;
            level.Tiles[5 + idX][idY] = byte & 0b00000100;
            level.Tiles[6 + idX][idY] = byte & 0b00000010;
            level.Tiles[7 + idX][idY] = byte & 0b00000001;
            ++b;
        }
        --idY;
    }
    m_Levels.push_back(level);
}
