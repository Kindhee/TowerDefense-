#include "GameWindow.h"

GameWindow::GameWindow() {

}

int GameWindow::game() {

    srand(time(NULL));

    //Cr�ation d'une fen�tre
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "SFML");

    // mouse
    sf::Mouse mouse;
    // 

    // font
    sf::Font font;
    font.loadFromFile("font/font.ttf");
    //
    
    // text_coins
    sf::Text text_coins;
    text_coins.setCharacterSize(15);
    text_coins.setFillColor(sf::Color::White);

    text_coins.setFont(font);
    text_coins.setPosition(0, 40);
    //

    // text_health
    sf::Text text_health;
    text_health.setCharacterSize(15);
    text_health.setFillColor(sf::Color::White);

    text_health.setFont(font);
    text_health.setPosition(0, 20);
    //

    // text_level
    sf::Text text_level;
    text_level.setCharacterSize(15);
    text_level.setFillColor(sf::Color::White);

    text_level.setFont(font);
    text_level.setPosition(0, 0);
    //
    
    // init canon
    const char* img_canon = "img/canon.png";
    Canon canon_manager;
    //

    // canon
    vector<GameObject*> tab_canon;
    // 
    
    // balls
    vector<Ball*> tab_balls;
    vector<int> tab_index_delete;
    const char* img_ball = "img/ball.png";
    //

    // grid
    LevelCreater level;
    vector<Brick*> tab_brick;
    vector<Brick*> tab_map;
    int count_level = 0;
    //

    sf::Clock clock;
    float delta_time = 0;

    int limit_ball = 1;
    int limit_canon = 20;

    int min;
    int index;

    // vie
    int health = 3;
    // 
    
    // ressource 
    int coins = 100;
    //

    //GameLoop
    while (window->isOpen())
    {

        //EVENT

        if (tab_brick.size() == 0) {
            if (count_level < 4) {
                count_level += 1;
                tab_balls.clear();
                tab_brick = level.loadTable(count_level);
                tab_map.clear();
                tab_map = level.loadGrid(count_level);
            }
        }

        sf::Event oEvent;
        while (window->pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed) {
                window->close();
            }

            if (oEvent.type == sf::Event::MouseButtonPressed) {
                switch (oEvent.mouseButton.button) {
                case sf::Mouse::Left:

                    sf::Vector2i mouse_pos = mouse.getPosition(*window);
                    cout << "x" << mouse_pos.x << "y" << mouse_pos.y << endl;

                    for (int i = 0; i < tab_map.size(); i++) {

                        if (tab_map[i]->mouseOnBrick(mouse_pos.x, mouse_pos.y) == true && tab_canon.size() < limit_canon && coins >= 100) {

                            sf::Vector2i mouse_pos = mouse.getPosition(*window);

                            tab_canon.push_back(new GameObject(tab_map[i]->x + tab_map[i]->width / 2, tab_map[i]->y + tab_map[i]->height / 2, 100, 100, img_canon));

                            tab_canon[tab_canon.size() - 1]->setOriginToCenter();
                            tab_canon[tab_canon.size() - 1]->rotate(45);

                            coins -= 100;
                        }
                    }
                }
            }
        }
      
        if (tab_brick.size() != 0) {
            if (tab_balls.size() < limit_ball) {
                min = tab_brick[0]->y;
                index = 0;
                for (int i = 0; i < tab_brick.size(); i++) {
                    if (min < tab_brick[i]->y && tab_brick[i]->y < 1000) {
                        index = i;
                    }
                }

                if (tab_canon.size() != 0) {
                    for (int i = 0; i < tab_canon.size(); i++) {
                        if (tab_brick[index]->y >= 0) {

                            canon_manager.getVect(tab_canon[i]->shape, window, tab_brick[index]->shape);

                            tab_balls.push_back(new Ball(tab_canon[i]->x, tab_canon[i]->y, 10, img_ball));

                            float norme = sqrt(pow(canon_manager.vect_x, 2) + pow(canon_manager.vect_y, 2));

                            tab_balls[tab_balls.size() - 1]->vectX = canon_manager.vect_x / norme;
                            tab_balls[tab_balls.size() - 1]->vectY = canon_manager.vect_y / norme;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < tab_brick.size(); i++) {
            tab_brick[i]->moveDirection(delta_time,0,1,tab_brick[i]->speed);
            if (tab_brick[i]->y > window->getSize().y) {
                health--;
                coins += tab_brick[i]->reward;
                tab_brick.erase(tab_brick.begin() + i);
                i--;
            }
        }

        for (auto it = tab_balls.begin(); it != tab_balls.end(); ) {
            (*it)->moveDirection(delta_time, (*it)->vectX, (*it)->vectY, (*it)->speed);

            if (tab_brick.size() != 0) {
                bool ballRemoved = false;  

                for (int j = 0; j < tab_brick.size(); j++) {
                    if ((*it)->hasCollided(tab_brick[j]->shape, tab_brick[j]->width, tab_brick[j]->height)) {
                        tab_brick[j]->update();

                        if (tab_brick[j]->health <= 0) {
                            coins += tab_brick[j]->reward;
                            tab_brick.erase(tab_brick.begin() + j);
                            j--;
                        }

                        it = tab_balls.erase(it);
                        ballRemoved = true;
                        break;
                    }
                }

                if (ballRemoved) {
                    continue;
                }
            }

            if ((*it)->windowCollided(window)) {
                it = tab_balls.erase(it);
                continue;
            }

            ++it;
        }

        std::stringstream str_coins;
        str_coins << "coins :" << coins;
        text_coins.setString(str_coins.str());

        std::stringstream str_health;
        str_health << "health :" << health;
        text_health.setString(str_health.str());

        std::stringstream str_level;
        str_level << "level :" << count_level;
        text_level.setString(str_level.str());

        //DRAW
        window->clear();

        if (tab_map.size() != 0) {
            for (int i = 0; i < tab_map.size(); i++) {
                window->draw(*tab_map[i]->shape);
            }
        }

        if (tab_brick.size() != 0) {
            for (int i = 0; i < tab_brick.size(); i++) {
                window->draw(*tab_brick[i]->shape);
            }
        }

        if (tab_balls.size() != 0) {
            for (int i = 0; i < tab_balls.size(); i++) {
                window->draw(*tab_balls[i]->shape);
            }
        }

        if (tab_canon.size() != 0) {
            for (int i = 0; i < tab_canon.size(); i++) {
                window->draw(*tab_canon[i]->shape);
            }
        }

        window->draw(text_coins);
        window->draw(text_health);
        window->draw(text_level);

        window->display();

        delta_time = clock.restart().asSeconds();

    }

    return 0;
}
