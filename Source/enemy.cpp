#include "headers/enemy.h"

namespace Game_N{

  Enemy::Enemy(sf::Vector2i pos)
  {
    alive_ = true;
  	detectPlayer_ = false;
  	position_ = pos;
  	maxHp_ = 100;
    name_ = "Enemy";
    hp_ = maxHp_;
  	lvl_ = 0;
  	strength_ = 5;
  	range_ = 3;
  	movingUp_ = false;
  	movingDown_ = false;
  	movingLeft_ = false;
  	movingRight_ = false;
  }

  Enemy::Enemy(int lvl, int strength, int range, int damage, int x, int y, std::string name, sf::Vector2i pos)
  {
    alive_ = true;
    lvl_ = lvl;
    strength_ = strength;
    range_ = range;
    damage_ = damage;
    xCoord_ = x;
    yCoord_ = y;
    name_ = name;
    position_ = pos;

    movingUp_ = false;
  	movingDown_ = false;
  	movingLeft_ = false;
  	movingRight_ = false;

  }

  // void Enemy::

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
