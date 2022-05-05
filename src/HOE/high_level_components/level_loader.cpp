#include "level_loader.h"
#include <iostream>
#include <fstream>
#include <string>
#include "hflog.h"


LevelLoader::LevelLoader()
{
    m_CellSize = 32;
}

LevelLoader::LevelLoader(int cellSize)
{
    m_CellSize = cellSize;
}


std::vector<Block> LevelLoader::loadBlocks(std::string filePath, char symbol)
{
    std::vector<Block> blocks;

    std::ifstream file;
    file.open(filePath.c_str());
    if (!file.is_open())
    {
        HFLog::GetInstance().Log(HFLog::HF_ERROR, std::string("Tried to load level but the file at '") + filePath + "' could not be opened!", __FILE__, __LINE__);
        return blocks;
    }

    std::string line;

    int lineNum = 1;
    while (std::getline(file, line))
    {
        for (int i = 0; i < line.length(); i++)
        {
            char curSymbol = line.at(i);
            if (curSymbol == symbol)
            {
                blocks.push_back(Block(
                    HFMath::Vector2(m_CellSize, m_CellSize),
                    HFMath::Vector2(i * m_CellSize, (lineNum - 1) * m_CellSize)
                ));
            }
        }

        lineNum++;
    }

    file.close();

    return blocks;
}
