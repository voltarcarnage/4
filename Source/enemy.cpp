#include "headers/enemy.h"

namespace Game_N{

  Enemy::Enemy(sf::Vector2i pos)
  {
    alive_ = true;
    // fraction_ = fraction;
  	detectHero_ = false;
  	position_ = pos;
  	maxHp_ = 100;
    name_ = "Enemy";
    hp_ = maxHp_;
  	lvl_ = 0;
  	damage_ = 5;
  	range_ = 3;

  	movingUp_ = false;
  	movingDown_ = false;
  	movingLeft_ = false;
  	movingRight_ = false;
  }

  Enemy::Enemy(int lvl, int range, int damage,std::string name, sf::Vector2i pos)
  {
    alive_ = true;
    lvl_ = lvl;
    range_ = range;
    damage_ = damage;
    // fraction_ = fraction;
    name_ = name;
    position_ = pos;

    movingUp_ = false;
  	movingDown_ = false;
  	movingLeft_ = false;
  	movingRight_ = false;

  }

  void Enemy::gainLvl(int lvl)
  {
    lvl_ += lvl;
    maxHp_ = maxHp_ * pow(1.1, lvl_);
    hp_ = hp_ * pow(1.1, lvl_);
    damage_ += 3;
  }

  bool Enemy::takeDamage(int dmg)
  {
    return (hp_ -= dmg) > 0 ? true : false;
  }

  bool Enemy::isAlive()
  {
    return alive_;
  }

  void Enemy::die()
  {
    alive_ = false;
  }

  void Enemy::stopMove()
  {
    movingUp_ = false;
    movingDown_ = false;
    movingLeft_ = false;
    movingRight_ = false;
    movingDir_ = Stop;
  }

  int Enemy::faceWhere()
  {
    if(facingDir_ == Up){
      return 1;
    }
    else if(facingDir_ == Down){
      return 2;
    }
    else if(facingDir_ == Left){
      return 3;
    }
    else if(facingDir_ == Right){
      return 4;
    }

    return 0;
  }

  void Enemy::faceThere(int direction)
  {
    switch(direction)
    {
      case 1:
        facingDir_ = Up;
        break;
      case 2:
        facingDir_ = Down;
        break;
      case 3:
        facingDir_ = Left;
        break;
      case 4:
        facingDir_ = Right;
        break;
    }
  }

  void Enemy::moveUp()
  {
    stopMove();
    movingUp_ = true;
    faceThere(1);
    position_.y -= 1;
  }

  void Enemy::moveDown()
  {
    stopMove();
    movingDown_ = true;
    faceThere(2);
    position_.y += 1;
  }

  void Enemy::moveLeft()
  {
    stopMove();
    movingLeft_ = true;
    faceThere(3);
    position_.x -= 1;
  }

  void Enemy::moveRight()
  {
    stopMove();
    movingRight_ = true;
    faceThere(4);
    position_.x += 1;
  }

  void Enemy::detectHero(sf::Vector2i pos)
  {
    detectHero_ = true;
    setTargetPos(pos);
  }

  void Enemy::undetectHero()
  {
    detectHero_ = false;
  }

  void Enemy::setTargetPos(sf::Vector2i pos)
  {
    heroPos_ = pos;
    targetFreshness_ = 3;
  }

  bool Enemy::canMove(std::vector<std::vector<int>>& map)
  {
    switch(movingDir_)
    {
      case Up:
        return (map[xCoord_][yCoord_ - 1] == 0);
      case Down:
        return (map[xCoord_][yCoord_ + 1] == 0);
      case Left:
        return (map[xCoord_ - 1][yCoord_] == 0);
      case Right:
        return (map[xCoord_ + 1][yCoord_] == 0);
    }

    return false;
  }

  void Enemy::moveToHero(std::vector<std::vector<int>>& map)
  {
    int dx,dy,ex,ey,hx,hy;
    bool horizont = false;

    ex = position_.x; ey = position_.y;
    hx = heroPos_.x; hy = heroPos_.y;
    dx = hx - ex;
    dy = hy - ey;

    if(std::abs(dx) > std::abs(dy))
      horizont = true;

    std::vector<int> dir(2);

    if(dx > 0)
      dir[0] = 1;
    else if(dx < 0)
      dir[0] = -1;
    else dir[0] = 0;

    if(dy > 0)
      dir[1] = 1;
    else if(dy < 0)
      dir[1] = -1;
    else dir[1] = 0;

    if(horizont)
    {

      if(dir[0]){
        movingDir_ = Right;
        if(canMove(map))
          moveRight();
      }
      else if(dir[0] == -1){
        movingDir_ = Left;
        if(canMove(map))
          moveLeft();
      }


    }
    else
    {
      if(dir[1]){
        movingDir_ = Down;
        if(canMove(map)){
          moveDown();
        }
      }
      else if(dir[1] == -1){
        movingDir_ = Up;
        if(canMove(map)){
          moveUp();
        }
      }
    }
  }

  bool Enemy::isFreshTarget()
  {
    if(targetFreshness_)
    {
      targetFreshness_--;
      return true;
    }
    return false;
  }

}
