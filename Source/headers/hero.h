
#include "entity.h"
#include "enemy.h"
#include "spells.h"

#pragma once
namespace Game_N{

  class Hero : public Entity{
    private:
      int lvl_;
      int exp_;
      int mana_;
      int maxMana_;
      int expToNextLvl_;
      int range_;
      int amountOfUndeads_;
      std::vector<Enemy> undeads_;
      std::map<std::string, Spells* > spell_;
    public:
      Hero();
      Hero(std::string name, int lvl, int exp, int mana, int maxMana, int expToNextLvl, int amountOfUndeads, int range);

      int getLvl() const {return lvl_;}
      int getExp() const {return exp_;}
      int getMana() const {return mana_;}
      int getMaxMana() const {return maxMana_;}
      int getExpToNextLvl() const {return expToNextLvl_;}
      int getRange() const {return range_;}
      // int getUndeads() const;

      bool takeDamage(int damage);

      void gainExp(int exp);
      void lvlUp();
      void heal(int heal, int mana);

      void setRange(int range) {range_ = range;}
      void setLvl(int lvl) {lvl_ = lvl;}
      void setExp(int exp) {exp_ = exp;}
      void setMana(int mana) {mana_ = mana;}
      void setMaxMana(int maxMana) {maxMana_ = maxMana;}
      void setExpToNextLvl(int nextLvl) {expToNextLvl_ = nextLvl;}
      // void setStrength(int strength) {strength_ = strength;} Don't use

      ~Hero();
  };

}
