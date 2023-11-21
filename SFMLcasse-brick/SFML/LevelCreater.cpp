#include "LevelCreater.h"

LevelCreater::LevelCreater() {

	img_brick_blue = "img/blue-full.png";
	img_brick_red = "img/red-full.png";
	img_brick_yellow = "img/yellow-full.png";

}

vector<Brick*> LevelCreater::loadTable(int level) {
    vector<Brick*> list;
    std::string path = "level/" + std::to_string(level) + ".txt";

    std::ifstream levelTxt(path);
    std::string row;

    int X = 50;
    int Y = 100;

    while (std::getline(levelTxt, row))
    {
        for (int j = 0; j < 12; j++)
        {
            if (row[j] == '1')
            {
                list.push_back(new Brick(X, Y, 80, 25, img_brick_blue, 1));
            }
            if (row[j] == '2')
            {
                list.push_back(new Brick(X, Y, 80, 25, img_brick_red, 3));
            }
            if (row[j] == '3')
            {
                list.push_back(new Brick(X, Y, 80, 25, img_brick_yellow, 5));
            }
            X += 80;
        }
        X = 50;
        Y += 25;
    }
    return list;
}


//vector<Brick*> LevelCreater::loadTable(int level) {
//		vector<Brick*> list;
//		if (level == 1) {
//			int X = 50;
//			int Y = 100;
//			for (int j = 0; j < 15; j++) {
//				for (int i = 0; i < 11; i++) {
//					list.push_back(new Brick(X, Y, 80, 25, img_brick_blue, 1));
//					X += 80;
//				}
//				X = 50;
//				Y += 30;
//			}
//			return list;
//		}		
//		
//		if (level == 2) {
//			int X = 50;
//			int Y = 100;
//			for (int j = 0; j < 15; j++) {
//				for (int i = 0; i < 11; i++) {
//					list.push_back(new Brick(X, Y, 80, 25, img_brick_yellow, 2));
//					X += 80;
//				}
//				X = 50;
//				Y += 30;
//			}
//			return list;
//		}		
//		
//		if (level == 3) {
//			int X = 50;
//			int Y = 100;
//			for (int j = 0; j < 15; j++) {
//				for (int i = 0; i < 11; i++) {
//					list.push_back(new Brick(X, Y, 80, 25, img_brick_red, 3));
//					X += 80;
//				}
//				X = 50;
//				Y += 30;
//			}
//			return list;
//		}
//}

