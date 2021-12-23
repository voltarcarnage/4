#include "enemy.h"

#pragma once
namespace Game_N{

  class Summoner : public Enemy{
    private:
      std::vector<Enemy> summoned_;
    public:
      Summoner();
      Summoner(int lvl, int range, int damage, bool undead, std::string name, sf::Vector2f pos,sf::Color color);

      std::vector<Enemy>& getSummoned() {return summoned_;}
  };

}
