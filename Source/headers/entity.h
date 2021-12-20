#include <iostream>
#include <string>
#include <map>
#include <vector>

#pragma once

namespace Game_N{

  class Entity{
    protected:
      enum Fractions {Goblin, Skeleton, Orc, Golem, Human};
      std::string name_;
      unsigned int maxHp_;
      unsigned int hp_;
      unsigned int damage_;
      Fractions fraction_;
      unsigned int speed_;
      int xCoord_;
      int yCoord_;
    public:
      Entity();
      // Entity(std::string name, Fractions fraction);

      std::string getName() const {return name_;}
      int getHp() const {return hp_;}
      int getMaxHp() const {return maxHp_;}
      int getDamage() const {return damage_;}
      int getSpeed() const {return speed_;}
      int getX() const {return xCoord_;}
      int getY() const {return yCoord_;}
      int getFraction() const {return fraction_;}
      void setName(std::string name) {name_ = name;}
      void setHp(int hp) {hp_ = hp;}
      void setMaxHp(int max_hp) {maxHp_ = max_hp;}
      void setDamage(int damage) {damage_ = damage;}
      void setSpeed(int speed) {speed_ = speed;}
      void setX(int x) {xCoord_ = x;}
      void setY(int y) {yCoord_ = y;}
      void setFraction(Fractions fraction) {fraction_ = fraction;}
  };

}
