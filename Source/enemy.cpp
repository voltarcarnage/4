#include "headers/enemy.h"

namespace Game_N{

  Enemy::Enemy()
  {

  }

  void Enemy::gainLvl(int lvl)
  {
    lvl_ += lvl;
    maxHp_ = maxHp_ * 1.3 * lvl_ * 0.5;
  	hp_ = hp_ * 1.3 * lvl * 0.5;
  	damage_ += 2;
  	// agility+=2;
  	// defense+=2;
  }

  bool Enemy::takeDamage(int dmg)
  {
    hp_ -= dmg;
    if(hp_ > 0)
      return true;
    return false;
  }

  bool Enemy::isAlive()
  {
    return alive_;
  }

  void Enemy::die()
  {
    alive_ = false;
  }

}
