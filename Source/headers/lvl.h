#include "SFML/Graphics.hpp"
#include "enemy.h"
#include "cell.h"

#pragma once

namespace Game_N{

  class Level {
    private:
        std::string mapStr_;
        std::vector<Enemy> enemies_;
        std::vector<std::vector<Cell>> mapCell_;
    public:
        Level();
        Level(int num);
        Level(const Level& );
        int getTileType(sf::Vector2f coords);
        sf::Vector2f getHeroCoord();
        std::vector<std::vector<Cell>>& getCell(){ return mapCell_; };
        std::vector<Enemy>& getEnemies(){ return enemies_; };
  };
}
