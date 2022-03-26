#pragma once
#include "block.h"
#include "sprite.h"


class LevelLoader
{
public:
    LevelLoader();
    LevelLoader(int cellSize);
    std::vector<Block> loadBlocks(const char* filePath, char symbol);

private:
    int m_CellSize;
};
