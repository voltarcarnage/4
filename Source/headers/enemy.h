
#include "entity.h"
#include "spells.h"

#pragma once

namespace Game_N{

  class Enemy : public Entity{
    private:
      enum Directions { Up, Down, Right, Left, Stop };
      bool alive_, detectPlayer_;
      int lvl_;
      int strength_;
      int range_;
      int damage_;
      Necromancy necromancy;
    public:
      Enemy(); //SFML
      // Enemy(int lvl, int strength, int range, int damage, int x, int y); SFML

      int getLvl() const {return lvl_;}
      int getStrength() const {return strength_;}
      int getRange() const {return range_;}
      int getDamage() const {return damage_;}

      void setLvl(int lvl) {lvl_ = lvl;}
      void setStrength(int strength) {strength_ = strength;}
      void setRange(int range) {range_ = range;}
      void setDamage(int damage) {damage_ = damage;}

      void gainLvl(int lvl);

      // void followToHero();
      void getPos(); //SFML vector
      // void setPos(int x, int y) {xCoord_ = x; yCoord_ = y;}
      bool takeDamage(int dmg);
      bool isAlive();
      void die();


      bool moveUp();
      bool moveDown();
      bool moveLeft();
      bool moveRight();
      bool movesUp();
      bool movesDown();
      bool movesLeft();
      bool movesRight();
      bool stopMove();

      bool canMove(std::vector<std::vector<int>>& map);
      void moveToTarget(std::vector<std::vector<int>>& map);
		  // int faceWhere();
		  // void faceThere(int dir);

  };

}
