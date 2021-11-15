#include "Level.h"

void Level::loadMap(Map lvl_map, Window& window)
{
    switch (lvl_map)
    {
    case Map::ONE:
        level_file.open("LevelMap1.txt");
    case Map::TWO:
        level_file.open("LevelMap2.txt");
    case Map::THREE:
        level_file.open("LevelMap3.txt");

    default:
        break;
    }
    
    char wall = '#';
    int row_len = 22; //8
    int column_len = 16; //6

    float angle = 0.0f;
    float x = 0.0f;
    float y = 15.5f; //5.5f
    float z = 19.0f; //6.0f

    const float SPACING_X = 2.0f;
    const float SPACING_Y = 2.0f;
    const float SPACING_Z = 2.0f;

    while (!level_file.eof())
    {
        x++;
        if (x == (row_len + 1))
        {
            y--;
            x = 0;
        }
        if (level_file.get() == wall)
        {
            for (int i = 0; i < 2; i++)
            {
                //window.getRenderer().InitCube(angle, x * SPACING_X - (row_len + 1), y * SPACING_Y - column_len, z + (SPACING_Z * i));
            }
        }
    }
    level_file.close();
}
