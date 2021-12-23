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
    damage_ = 10;
    amountOfUndeads_ = 2;
    coords_ = sf::Vector2f(0.f, 0.f);
    circle_.setSize(sf::Vector2f(60.f,60.f));
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

  bool Hero::detectEnemy(sf::Vector2f coords)
  {
    sf::Vector2f direction;
    direction.x = coords.x - circle_.getPosition().x;
    direction.y = coords.y - circle_.getPosition().y;
    double dxy = sqrt(direction.x * direction.x + direction.y * direction.y);

    if(dxy <= spell_["necromancy"]->getRangeOfSpell() || dxy <= spell_["curse"]->getRangeOfSpell() || dxy <= spell_["morphism"]->getRangeOfSpell() || dxy <= spell_["desiccation"]->getRangeOfSpell())
      return true;

    return false;
  }

  Spells* Hero::getSpell(std::string spell,sf::Vector2f coords)
  {
    if(detectEnemy(coords))
    {
      if(spell == "necromancy")
        return spell_["necromancy"];
      else if(spell == "curse")
        return spell_["curse"];
      else if(spell == "morphism")
        return spell_["morphism"];
      else if(spell == "desiccation")
        return spell_["desiccation"];
    }

    return NULL;
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
    maxMana_ += (lvl_ * 0.41) * 41;
    mana_ = maxMana_;
    expToNextLvl_ += (lvl_ * 0.8)*100;
    exp_ = 0;
    spell_["necromancy"]->lvlUpSpell();
    spell_["curse"]->lvlUpSpell();
    spell_["morphism"]->lvlUpSpell();
    spell_["desiccation"]->lvlUpSpell();
    switch(lvl_){
      case 1:
        amountOfUndeads_ = 3;
      case 3:
        amountOfUndeads_ = 4;
      case 6:
        amountOfUndeads_ = 6;
    }
  }

  void Hero::healHp(int heal)
  {
    hp_ += heal;

    if(hp_ > maxHp_)
      hp_ = maxHp_;
  }

  void Hero::healMana(int mana)
  {
    mana_ += mana;

    if(mana_ > maxMana_)
      mana_ = maxMana_;
  }

  void Hero::castASpell(std::string spell,Enemy& enemy)
  {
    if(spell == "desiccationH")
    {
      decreaseMana(spell_["desiccation"]->getManaCost());
      healHp(spell_["desiccation"]->getE() * 40);
    }
    else if(spell == "desiccationM")
    {
      decreaseMana(spell_["desiccation"]->getManaCost());
      healMana(spell_["desiccation"]->getE() * 40 * 0.8);
    }
    else if(spell == "necromancy")
    {
      enemy.setAlive(true);
      // enemy.setRectangleColor(sf::Color(232,121,62));
      undeads_.push_back(enemy);
      undeadsNames_.push_back(enemy.getName());
      decreaseMana(spell_["necromancy"]->getManaCost());
    }
    else if(spell == "morphism")
    {
      std::string name_str;
      int k;
      bool nameIn = false;
      std::cin >> name_str;
      for(int i = 0; i < undeadsNames_.size(); i++)
      {
        if(undeadsNames_[i] == name_str){
          nameIn = true;
          k = i;
          break;
        }
      }
      if(nameIn)
      {
        for(int i = 0; i < undeads_.size(); i++)
        {
          if(detectEnemy(undeads_[i].getCell().getRectangle().getPosition()))
          {
            if(!(undeads_[i].getName().find("-") != std::string::npos)){
            std::cout << undeads_[i].getDamage() << " ";
            undeads_[i].setName(undeads_[i].getName() + "-" + name_str);
            undeads_[i].setDamage(undeads_[i].getDamage() + undeads_[k].getDamage());
            undeads_[i].setHp(undeads_[i].getHp() + undeads_[k].getHp());
            std::cout << undeads_[i].getDamage() << std::endl;
            break;
            }
            else
              continue;
          }
        }
        decreaseMana(spell_["morphism"]->getManaCost());
      }
      else{
        std::cout << "You don't know this type of enemy" << std::endl;
      }
    }
  }

  // Hero::~Hero()
  // {
  //   // for(auto iter = spell_.begin(); iter != spell_.end(); iter++)
  //   //   delete *iter->second;
  //
  //   delete spell_["necromancy"];
  //   delete spell_["curse"];
  //   delete spell_["morphism"];
  //   delete spell_["desiccation"];
  // }

}
