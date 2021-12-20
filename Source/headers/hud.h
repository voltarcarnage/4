#include <sstream>
#include "SFML/Graphics.hpp"
#include "hero.h"

#pragma once

namespace Game_N{

  class HUD{
    private:
      unsigned int dngLvl_;

      int bordersize_,width_,height_,startx_,starty_;

      int heroMaxHp_,heroHp_,heroStr_,heroMaxMana_,heroMana_,heroLvl_,heroExp_, heroExpToNextLvl_;

      sf::Color fillColor_;
      sf::Color borderColor_;

      sf::Font font_;
      sf::Text text_;


    	void drawStats(sf::RenderWindow & window, const Hero &);
      // void drawTextBox(sf::RenderWindow & window);
    public:
      HUD(); //Default constructor
      HUD(Hero& hero);

    	void drawHUD(sf::RenderWindow & window,const Hero &);
    	void sendMsg(std::string s);
    	void updateStats(Hero& hero,unsigned int lvl);
  };

}
