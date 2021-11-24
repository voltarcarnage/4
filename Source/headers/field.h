#include "hero.h"
#include "alive_enemy.h"

#pragma once

namespace Game_N{

  class Field{
    private:
      Hero hero_;
      std::vector<std::vector<int>> map_;
      std::vector<Enemy> enemies_;
      std::vector<AliveEnemy> aliveEnemies_;
      int x_,y_;
    public:
      Field();
      int getXMap() const {return x_;}
      int getYMap() const {return y_;}
      void setSizeOfMap(int x, int y) {x_ = x; y_ = y;}
      void setXMap(int x) {x_ = x;}
      void setYMap(int y) {y_ = y;}
      void openDoor();
      void closeDoor();
  };

}
