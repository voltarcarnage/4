#include "hero.h"
#include "lvl.h"
// #include "time.h"
#include "SFML/Graphics.hpp"
// #include "HUD.h"
#include <iostream>

#pragma once

namespace Game_N{

  class GameManager{
    private:
        sf::Clock clock_; //timer
        Hero hero_; //hero
        std::vector<Level> levels_;//level
        int level_;//lvl at the moment
        sf::RenderWindow window_;
        // HUD hud; //hud
        bool UP_,DOWN_,LEFT_,RIGHT_,HIT_,INTERACT_,NUM1_,NUM2_;
        void input(sf::Keyboard::Key key, bool pressed);
    public:
        GameManager();
        void chooseEvent();//chooses what to do (close/press/release key)
        // void updatePlayer(sf::Time dt);//updating movement and etc
        // void updateEnemy(sf::Time dt);//updating movement and etc
        void moveHero();
        void interactionWithMap();
        void update();//prints all stuff
        void start();//run
        // void changeLevel();
    };

}
