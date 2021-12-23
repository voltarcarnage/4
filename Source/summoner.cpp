#include "headers/summoner.h"

namespace Game_N{

  Summoner::Summoner()
  {
    alive_ = true;
    // fraction_ = fraction;
  	detectHero_ = false;
  	// position_ = pos;
  	maxHp_ = 100;
    name_ = "Enemy";
    hp_ = maxHp_;
  	lvl_ = 0;
  	damage_ = 5;
  	range_ = 3;

    // cell_ = Cell(pos,2,sf::Color(255,0,0));

  	movingUp_ = false;
  	movingDown_ = false;
  	movingLeft_ = false;
  	movingRight_ = false;
  }

  Summoner::Summoner(int lvl, int range, int damage, bool undead, std::string name, sf::Vector2f pos,sf::Color color)
  {
    alive_ = true;
    lvl_ = lvl;
    range_ = range;
    damage_ = damage;
    // fraction_ = fraction;
    name_ = name;
    position_ = pos;

    cell_ = Cell(pos,2,color);

    movingUp_ = false;
  	movingDown_ = false;
  	movingLeft_ = false;
  	movingRight_ = false;

    undead_ = undead;
  }

}
