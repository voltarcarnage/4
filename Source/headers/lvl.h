#include "SFML/Graphics.hpp"
#include "enemy.h"
#include "cell.h"
// #include "summoner.h"

#pragma once

namespace Game_N{

  class Level {
    private:
        // std::vector<Summoner> summoner_;
        std::string mapStr_;
        std::vector<Enemy> enemies_;
        std::vector<std::vector<Cell>> mapCell_;
    public:
        Level();
        Level(int num);
        Level(const Level& );

        int getTileType(sf::Vector2f coords);
        sf::Vector2f getHeroCoord();

        Cell getCellType(sf::Vector2f coords);

        void setTileType(sf::Vector2f coords, Cell cell) ;
        std::vector<std::vector<Cell>>& getCell(){ return mapCell_; }
        void addCell(std::vector<Cell> cell){ mapCell_.push_back(cell); }
        std::vector<Enemy>& getEnemies(){ return enemies_; }
        void addEnemy(Enemy enemy) {enemies_.push_back(enemy);}
        // std::vector<Summoner>& getSummoners() {return summoner_;}
  };
}
