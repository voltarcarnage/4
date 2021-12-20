#include "table.h"
#include "entity.h"
#include "enemy.h"
#include "spells.h"

#pragma once
namespace Game_N{

  class Hero : public Entity{
    private:
      int lvl_;
      int exp_;
      unsigned int mana_;
      unsigned int maxMana_;
      int expToNextLvl_;
      int range_;
      int amountOfUndeads_;
      std::vector<Enemy> undeads_;
      Table<std::string, Spells* > spell_;
      sf::Vector2f coords_;
      sf::Clock clock_;
      sf::RectangleShape circle_;
    public:
      Hero();
      Hero(int lvl,int maxHp, int damage, int exp, int maxMana, int expToNextLvl, int amountOfUndeads, int range);

      int getLvl() const {return lvl_;}
      int getExp() const {return exp_;}
      int getMana() const {return mana_;}
      int getMaxMana() const {return maxMana_;}
      int getExpToNextLvl() const {return expToNextLvl_;}
      int getRange() const {return range_;}
      int getUndeads() const {return amountOfUndeads_;}
      sf::RectangleShape getShape() const {return circle_;}
      sf::Vector2f getCoords(){ return circle_.getPosition(); };
      sf::Time getClock() const { return clock_.getElapsedTime(); };

      void restartClock() { clock_.restart(); };
      bool takeDamage(int damage);
      bool isAlive();

      void decreaseMana(int mana) {mana_ -= mana;}
      void gainExp(int exp);
      void lvlUp();
      void healHp(int heal);
      void healMana(int mana);

      std::vector<Enemy>& getUndeadsV() {return undeads_;}

      bool detectEnemy(sf::Vector2f coords);
      void setRange(int range) {range_ = range;}
      void setLvl(int lvl) {lvl_ = lvl;}
      void setExp(int exp) {exp_ = exp;}
      void setMana(int mana) {mana_ = mana;}
      void setMaxMana(int maxMana) {maxMana_ = maxMana;}
      void setExpToNextLvl(int nextLvl) {expToNextLvl_ = nextLvl;}
      void castASpell(std::string spell,Enemy& enemy);

      Spells* getSpell(std::string spell,sf::Vector2f coords);

      void setCoords(sf::Vector2f coords){ circle_.setPosition(coords); };
      // ~Hero();
      // void setStrength(int strength) {strength_ = strength;} Don't use
  };

}
