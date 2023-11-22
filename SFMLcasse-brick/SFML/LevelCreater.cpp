#include "LevelCreater.h"

LevelCreater::LevelCreater() {

	ennemy_one = "img/dragon_type1.png";
    ennemy_two = "img/dragon_type2.png";
    ennemy_three = "img/girl_type3.png";


    tile_one = "img/tile_one.png";
    tile_two = "img/tile_two.png";
    tile_three = "img/tile_three.png";
}

vector<Brick*> LevelCreater::loadTable(int level) {
    vector<Brick*> list;
    std::string path = "level/" + std::to_string(level) + ".txt";

    std::ifstream levelTxt(path);
    std::string row;

    int X = 200;
    int Y = -400;

    while (std::getline(levelTxt, row))
    {
        for (int j = 0; j < 11; j++)
        {
            if (row[j] == '1')
            {
                list.push_back(new Brick(X, Y, 60, 60, ennemy_one, 2, 2, 50));
            }
            if (row[j] == '2')
            {
                list.push_back(new Brick(X, Y, 60, 60, ennemy_two, 5, 5, 25));
            }
            if (row[j] == '3')
            {
                list.push_back(new Brick(X, Y, 60, 60, ennemy_three, 100, 25, 10));
            }
            X += 60;
        }
        X = 200;
        Y += 25;
    }
    return list;
}

vector<Brick*> LevelCreater::loadGrid(int level) {
    vector<Brick*> list;
    std::string path = "grid/" + std::to_string(level) + ".txt";

    std::ifstream levelTxt(path);
    std::string row;

    int X = 0;
    int Y = 0;

    while (std::getline(levelTxt, row))
    {
        for (int j = 0; j < 11; j++)
        {
            if (row[j] == '1')
            {
                list.push_back(new Brick(X, Y, 100, 100, tile_one, 0));
            }
            if (row[j] == '2')
            {
                list.push_back(new Brick(X, Y, 100, 100, tile_two, 1));
            }
            if (row[j] == '3')
            {
                list.push_back(new Brick(X, Y, 100, 100, tile_three, 0));
            }
            X += 100;
        }
        X = 0;
        Y += 100;
    }
    return list;
}