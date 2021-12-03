#include "headers/entity.h"

namespace Game_N{

  Entity::Entity()
  {
    maxHp_ = 100;
    hp_ = maxHp_;
    damage_ = 15;
    speed_ = 50;
  	xCoord_ = 0;
    yCoord_ = 0;
  }

}
