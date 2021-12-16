#include "headers/hero.h"

namespace Game_N{

  Hero::Hero()
  {
    lvl_ = 1;
    exp_ = 0;
    maxMana_ = 100;
    mana_ = maxMana_;
    expToNextLvl_ = 100;
    range_ = 2;
    amountOfUndeads_ = 2;
    coords_ = sf::Vector2f(0.f, 0.f);
    circle_.setRadius(30.f);
    circle_.setPosition(100.f, 100.f);
    circle_.setFillColor(sf::Color::Blue);
    Spells* necromancy = new Necromancy();
    Spells* curse = new Curse();
    Spells* morphism = new Morphism();
    Spells* desiccation = new Desiccation();
    spell_.addSpell("necromancy", necromancy);
    spell_.addSpell("curse", curse);
    spell_.addSpell("morphism", morphism);
    spell_.addSpell("desiccation", desiccation);
  }

  Hero::Hero(int lvl,int maxHp, int damage, int exp, int maxMana, int expToNextLvl, int amountOfUndeads, int range)
  {
    lvl_ = lvl;
    maxHp_ = maxHp;
    hp_ = maxHp_;
    damage_ = damage;
    exp_ = exp;
    maxMana_ = maxMana;
    mana_ = maxMana;
    expToNextLvl_ = expToNextLvl;
    range_ = range;
    amountOfUndeads_ = amountOfUndeads;
    Spells* necromancy = new Necromancy();
    Spells* curse = new Curse();
    Spells* morphism = new Morphism();
    Spells* desiccation = new Desiccation();
    spell_.addSpell("necromancy", necromancy);
    spell_.addSpell("curse", curse);
    spell_.addSpell("morphism", morphism);
    spell_.addSpell("desiccation", desiccation);
  }
  
  bool Hero::isAlive()
  {
    return (hp_ > 0 ? true : false);
  }

  bool Hero::takeDamage(int damage)
  {
    hp_ -= damage;

    if(hp_ > 0)
      return true;

    return false;
  }

  void Hero::gainExp(int exp)
  {
    exp_ += exp;
    if(exp_ >= expToNextLvl_)
      lvlUp();
  }

  void Hero::lvlUp()
  {
    lvl_ += 1;
    maxHp_ += (lvl_ * 0.41) * 41;
    hp_ = maxHp_;
    expToNextLvl_ += (lvl_ * 0.8)*100;
    switch(lvl_){
      case 3:
        amountOfUndeads_ = 3;
      case 6:
        amountOfUndeads_ = 4;
    }
  }

  void Hero::heal(int heal, int mana)
  {
    hp_ += heal;
    if(hp_ > maxHp_)
      hp_ = maxHp_;

    mana_ += mana;

    if(mana_ > maxMana_)
      mana_ = maxMana_;
  }

  void Hero::castASpell(int choice)
  {
    switch(choice)
    {
      case 0:
      {
        this->spell_["Necromance"]->castSpell();
      }
    }
  }

}
