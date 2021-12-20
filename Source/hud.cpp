#include "headers/hud.h"

namespace Game_N{

  HUD::HUD()
  {
    bordersize_ = 5;
  	width_ = 600;
  	height_ = 150;
  	startx_ = 0;
  	starty_ = 850;

  	fillColor_.r = 150;
  	fillColor_.g = 50;
  	fillColor_.b = 250;

  	borderColor_.r = 250;
  	borderColor_.r = 150;
  	borderColor_.r = 100;

  	heroMaxHp_ = 100;
  	heroHp_ = 100;
  	heroStr_ = 10;
    heroMaxMana_ = 100;
  	heroMana_= 100;
  	heroLvl_= 1;
  	heroExp_= 0;
  	heroExpToNextLvl_= 100;
    dngLvl_ = 1;
  }

  HUD::HUD(Hero &hero)
  {
    bordersize_ = 5;
  	width_ = 600;
  	height_ = 150;
  	startx_ = 0;
  	starty_ = 850;

  	fillColor_.r = 150;
  	fillColor_.g = 50;
  	fillColor_.b = 250;

  	borderColor_.r = 250;
  	borderColor_.r = 150;
  	borderColor_.r = 100;

    heroMaxHp_ = hero.getMaxHp();
    heroHp_ = hero.getHp();
    heroStr_ = hero.getDamage();
    heroMaxMana_ = hero.getMaxMana();
    heroMana_ = hero.getMana();
    heroLvl_ = hero.getLvl();
    heroExp_ = hero.getExp();
    heroExpToNextLvl_ = hero.getExpToNextLvl();
  }

  void HUD::updateStats(Hero& hero,unsigned int lvl)
  {
    heroMaxHp_ = hero.getMaxHp();
    heroHp_ = hero.getHp();
    heroStr_ = hero.getDamage();
    heroMaxMana_ = hero.getMaxMana();
    heroMana_ = hero.getMana();
    heroLvl_ = hero.getLvl();
    heroExp_ = hero.getExp();
    heroExpToNextLvl_ = hero.getExpToNextLvl();

    dngLvl_ = 0;
  }

  void HUD::drawHUD(sf::RenderWindow &window,const Hero& hero)
  {
    sf::RectangleShape rect(sf::Vector2f(width_- 2*bordersize_,height_-2*bordersize_));
  	rect.setFillColor(fillColor_);
  	rect.setOutlineThickness(bordersize_);
  	rect.setOutlineColor(borderColor_);
  	rect.setPosition(startx_+bordersize_,starty_+bordersize_);

    window.draw(rect);
  	drawStats(window,hero);
    // drawTextBox(window);
  }

  void HUD::drawStats(sf::RenderWindow & window, const Hero & hero)
  {
    std::ostringstream oss;

  	sf::Font font;
  	font.loadFromFile("resources/joystix_monospace.ttf");

  	sf::Text text;
  	text.setFont(font);
  	text.setCharacterSize(17);
  	text.setColor(sf::Color::Black);

  	oss<<"Dungeon lvl: "<<dngLvl_<<std::endl;
  	oss<<"Health: "<<hero.getHp()<<"/"<<hero.getMaxHp()<<std::endl;
    oss<<"Mana: "<<hero.getMana()<<"/"<<hero.getMaxMana()<<std::endl;
  	oss<<"Exp   : "<<hero.getExp()<<"/"<<hero.getExpToNextLvl()<<std::endl;
  	oss<<"Level : "<<hero.getLvl()<<std::endl;

  	std::string str1 = oss.str();
  	text.setString(str1);
  	text.setPosition(20,starty_+height_-bordersize_-6*5-5*20);
  	window.draw(text);

  	int hpbarsizex = 200;
  	int hpbarsizey = 20;
  	int hpbarx = 5;
  	int hpbary = 5;

  	sf::RectangleShape rect(sf::Vector2f(hpbarsizex,hpbarsizey));
  	sf::RectangleShape green(sf::Vector2f((static_cast<float>(hero.getHp()/hero.getMaxHp()))*hpbarsizex,hpbarsizey));
  	sf::RectangleShape red(sf::Vector2f((1-static_cast<float>(hero.getHp()/hero.getMaxHp()))*hpbarsizex,hpbarsizey));
  	green.setFillColor(sf::Color::Green);
  	green.setPosition(hpbarx,hpbary);
  	red.setFillColor(sf::Color::Red);
  	red.setPosition(static_cast<int>((hpbarx+static_cast<float>(hero.getHp()/hero.getMaxHp())*hpbarsizex)),hpbary);
  	rect.setFillColor(sf::Color::Transparent);
  	rect.setOutlineThickness(1);
  	rect.setOutlineColor(sf::Color::Black);
  	rect.setPosition(hpbarx,hpbary);
  	window.draw(rect);
  	window.draw(red);
  	window.draw(green);
  }

  /*void HUD::drawTextBox(sf::RenderWindow & window)
  {
  	sf::RectangleShape rect(sf::Vector2f(width_/3,height_-2*bordersize_-2*5));
  	rect.setFillColor(sf::Color::Black);
  	rect.setPosition(width_/2-(width_/6),starty_+bordersize_+5);
  	window.draw(rect);
  	int textx = static_cast<int>(rect.getPosition().x);
  	int texty = static_cast<int>(rect.getPosition().y);
  	int i;
  	sf::Font font;
  	font.loadFromFile("resources/ShareTech.ttf");
  	sf::Text text;
  	text.setFont(font);
  	text.setCharacterSize(14);
  	text.setColor(sf::Color::White);
  	for (i=0;i<messages.size();i++)
    {
  		if(i>5){
  			break;
  		}
  		text.setString(messages[i]);
  		text.setPosition(textx+10,texty+height-2*bordersize-7*5-i*20);
  		window.draw(text);

  	}

  }*/


}
