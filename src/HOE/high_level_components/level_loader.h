#pragma once
#include "block.h"
#include "sprite.h"
#include "hfmath.h"


class LevelLoader
{
public:
    LevelLoader();
    LevelLoader(int cellSize);
    std::vector<Block> loadBlocks(std::string filePath, char symbol);
    std::vector<HFMath::Vector2> loadPositions(std::string filePath, char symbol);

private:
    int m_CellSize;
};
