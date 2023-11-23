#include "GameController.h"

GameController::GameController() {

}

int GameController::game() {

    srand(time(NULL));

    //Cr�ation d'une fen�tre
    Window window_manager;

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
    float ball_spawn_time = 0;

    int limit_ball = 1;
    float shoot_delay = 0.25;
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
    // 
    // DEBUT STATE MACHINE
    //
    while (window_manager.window->isOpen())
    {

        if (tab_brick.size() == 0) {
            if (count_level < 4) {
                count_level += 1;
                tab_balls.clear();
                tab_brick = level.loadTable(count_level);
                tab_map.clear();
                tab_map = level.loadGrid(count_level);
            }
        }

        // 
        // DEBUT COMMAND PATTERN -- SOURIS BOUGE -- ON DEPLACE LA SOURIS SUR L'ECRAN
        //

        sf::Event oEvent;
        while (window_manager.window->pollEvent(oEvent))
        {

            // COMMAND PATTERN -- ON FERME LA WINDOW --
            if (oEvent.type == sf::Event::Closed) {
                //
                window_manager.window->close();
            }

            // COMMAND PATTERN -- ON CLIQUE --
            if (oEvent.type == sf::Event::MouseButtonPressed) {
                //
                switch (oEvent.mouseButton.button) {

                    // COMMAND PATTERN -- ON CLIQUE GAUCHE --
                case sf::Mouse::Left:
                    //

                    sf::Vector2i mouse_pos = mouse.getPosition(*window_manager.window);
                    cout << "x" << mouse_pos.x << "y" << mouse_pos.y << endl;

                    for (int i = 0; i < tab_map.size(); i++) {

                        if (tab_map[i]->mouseOnBrick(mouse_pos.x, mouse_pos.y) == true && tab_canon.size() < limit_canon && coins >= 100) {

                            sf::Vector2i mouse_pos = mouse.getPosition(*window_manager.window);

                            tab_canon.push_back(new GameObject(tab_map[i]->x + tab_map[i]->width / 2, tab_map[i]->y + tab_map[i]->height / 2, 100, 100, img_canon));

                            tab_canon[tab_canon.size() - 1]->setOriginToCenter();
                            tab_canon[tab_canon.size() - 1]->rotate(45);

                            coins -= 100;
                        }
                    }
                }
            }
        }

        // 
        // FIN COMMAND PATTERN -- SOURIS BOUGE -- ON REVIENS AU DEBUT
        //


        //
        // DEBUT STATE MACHINE TOWER -- IDLE / EST CONSTRUITE --
        //

        // PREPARATION DU STATE "VISE" 
        if (tab_brick.size() != 0) {
            if (ball_spawn_time > shoot_delay) {
                ball_spawn_time = 0;
                min = tab_brick[0]->y;
                index = 0;
                for (int i = 0; i < tab_brick.size(); i++) {
                    if (min < tab_brick[i]->y && tab_brick[i]->y < 1000) {
                        index = i;
                    }
                }
                //


                if (tab_canon.size() != 0) {
                    for (int i = 0; i < tab_canon.size(); i++) {
                        if (tab_brick[index]->y >= 0) {


                            // STATE MACHINE TOWER -- VISE --
                            canon_manager.getVect(tab_canon[i]->shape, tab_brick[index]->shape);
                            //

                            // STATE MACHINE TOWER -- TIRE --
                            tab_balls.push_back(new Ball(tab_canon[i]->x, tab_canon[i]->y, 10, img_ball));

                            float norme = sqrt(pow(canon_manager.vect_x, 2) + pow(canon_manager.vect_y, 2));

                            tab_balls[tab_balls.size() - 1]->vectX = canon_manager.vect_x / norme;
                            tab_balls[tab_balls.size() - 1]->vectY = canon_manager.vect_y / norme;
                            //
                        }
                    }
                }
            }
        }

        //
        // FIN STATE MACHINE TOWER RETOUR A -- IDLE --
        //

        for (int i = 0; i < tab_brick.size(); i++) {
            tab_brick[i]->moveDirection(delta_time,0,1,tab_brick[i]->speed);
            if (tab_brick[i]->y > window_manager.window->getSize().y) {
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

            if ((*it)->windowCollided(window_manager.window)) {
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

        sf::Texture endTexture;
        if (count_level >= 4 || health < 0) {
            tab_map.clear();
            tab_balls.clear();
            tab_brick.clear();
            tab_canon.clear();
            if (count_level >= 4) {
                endTexture.loadFromFile("img/Victory.png");
            }

            if (health < 0) {
                endTexture.loadFromFile("img/GameOver.png");

            }
        }
        sf::Sprite endSprite(endTexture);

        //DRAW
        window_manager.window->clear(sf::Color::White);

        if (tab_map.size() != 0) {
            for (int i = 0; i < tab_map.size(); i++) {
                window_manager.draw(tab_map[i]->shape);
            }
        }

        if (tab_brick.size() != 0) {
            for (int i = 0; i < tab_brick.size(); i++) {
                window_manager.draw(tab_brick[i]->shape);
            }
        }

        if (tab_balls.size() != 0) {
            for (int i = 0; i < tab_balls.size(); i++) {
                window_manager.draw(tab_balls[i]->shape);
            }
        }

        if (tab_canon.size() != 0) {
            for (int i = 0; i < tab_canon.size(); i++) {
                window_manager.draw(tab_canon[i]->shape);
            }
        }
        window_manager.draw(endSprite);

        window_manager.drawText(text_coins);
        window_manager.drawText(text_health);
        window_manager.drawText(text_level);

        window_manager.display();

        delta_time = clock.restart().asSeconds();
        ball_spawn_time += delta_time;

    }

    return 0;
}
