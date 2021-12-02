#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

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
      sf::Vector2i position_;
		  sf::Vector2i targetPos_;
      bool movingUp_,movingDown_,movingLeft_,movingRight_,faceUp_, faceDown_,faceLeft_,faceRight_;
      Necromancy necromancy;
    public:
      Enemy(sf::Vector2i pos); //SFML
      Enemy(int lvl, int strength, int range, int damage, int x, int y, std::string name, sf::Vector2i pos);

      int getLvl() const {return lvl_;}
      int getStrength() const {return strength_;}
      int getRange() const {return range_;}
      int getDamage() const {return damage_;}
      sf::Vector2i getPos() const {return position_;}

      void setLvl(int lvl) {lvl_ = lvl;}
      void setStrength(int strength) {strength_ = strength;}
      void setRange(int range) {range_ = range;}
      void setDamage(int damage) {damage_ = damage;}
      void setPos(unsigned int x, unsigned int y);
      void setImg(sf::Sprite& img);

      void setTargetPos(sf::Vector2i pos);
		  bool isFreshTarget();
		  void detectHero(sf::Vector2i pos);
		  void undetectHero();

      void gainLvl(int lvl);

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
		  int faceWhere();
		  void faceThere(int dir);

  };

}
