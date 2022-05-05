#pragma once
#include "block.h"
#include "sprite.h"


class LevelLoader
{
public:
    LevelLoader();
    LevelLoader(int cellSize);
    std::vector<Block> loadBlocks(std::string filePath, char symbol);

private:
    int m_CellSize;
};
