#include <iostream>
#include <ctime>
#include "hero.h"
#include "lvl.h"
// #include "time.h"
#include "SFML/Graphics.hpp"
#include "hud.h"
#include <cmath>

#pragma once

namespace Game_N{

  class GameManager{
    private:
        bool getExp_;
        HUD hud_;
        sf::Clock clock_; //timer
        Hero hero_; //hero
        std::vector<Level> levels_;//level
        int level_;//lvl at the moment
        sf::RenderWindow window_;
        bool UP_,DOWN_,LEFT_,RIGHT_,Z_,X_,C_,V_,INTERACT_,HP_,MANA_;
        void input(sf::Keyboard::Key key, bool pressed);
    public:
        GameManager();
        void chooseEvent();//chooses what to do (close/press/release key)
        // void updatePlayer(sf::Time dt);//updating movement and etc
        void updateUndeads(sf::Time dt);
        void updateEnemy(sf::Time dt);//updating movement and etc
        void moveHero();
        void heroCombat();
        void interactionWithMap();
        void update();//prints all stuff
        void start();//run
        // void changeLevel();
    };

}
