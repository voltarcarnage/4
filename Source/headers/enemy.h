#include <SFML/Graphics.hpp>
#include <cmath>

#include "cell.h"
#include "entity.h"
// #include "spells.h"

#pragma once

namespace Game_N{

  class Enemy : public Entity{
    protected:
      enum Directions { Up, Down, Right, Left, Stop };
      Directions facingDir_ = Up, movingDir_ = Stop;
      bool alive_, detectHero_, undead_;
      int lvl_;
      int range_;
      int targetFreshness_ = 0;
      sf::Vector2f position_;
		  sf::Vector2f heroPos_;
      sf::Clock clock_;
      sf::Text text_;
      sf::Font font_;
      bool movingUp_,movingDown_,movingLeft_,movingRight_,faceUp_, faceDown_,faceLeft_,faceRight_;
      // Necromancy necromancy;
      Cell cell_;
    public:
      Enemy();
      Enemy(sf::Vector2f pos); //SFML
      Enemy(int lvl, int range, int damage, bool undead, std::string name, sf::Vector2f pos,sf::Color color);

      int getLvl() const {return lvl_;}
      // int getStrength() const {return strength_;}
      int getRange() const {return range_;}
      int getDamage() const {return damage_;}
      Cell getCell() const {return cell_;}
      sf::Vector2f getPos() const {return position_;}

      sf::Text& getText() {return text_;}
      sf::Font& getFont() {return font_;}

      void setText(sf::Text text) {text_ = text;}
      void setFont(sf::Font font) {font_ = font;}

      bool getState() const {return undead_;}
      void setState(bool undead) {undead_ = undead;}

      void setLvl(int lvl) {lvl_ = lvl;}
      // void setStrength(int strength) {strength_ = strength;}
      void setRange(int range) {range_ = range;}
      void setDamage(int damage) {damage_ = damage;}
      void setPos(sf::Vector2f pos) {position_ = pos;}
      // void setImg(sf::Sprite& img);
      sf::Time getClock() const { return clock_.getElapsedTime(); };
      void restartClock() { clock_.restart(); };

      // sf::RectangleShape& getHpBar() {return hpBar_;}

      void setTargetPos(sf::Vector2f pos);
		  bool isFreshTarget();
		  void detectHero(sf::Vector2f pos);
		  void undetectHero();

      void gainLvl(int lvl);

      void setRectangleColor(sf::Color color) {cell_.getRectangle().setFillColor(color);}

      bool takeDamage(int dmg);
      bool isAlive();
      void setAlive(bool alive) {alive_ = alive;}
      void die();


      void moveUp();
      void moveDown();
      void moveLeft();
      void moveRight();

      bool movesUp() const {return movingUp_;}
      bool movesDown() const {return movingDown_;}
      bool movesLeft() const {return movingLeft_;}
      bool movesRight() const {return movingRight_;}

      void move(sf::Vector2f coords);

      void stopMove();

      bool canMove(std::vector<std::vector<int>>& map);
      void moveToHero(std::vector<std::vector<int>>& map);

      int faceWhere();
		  void faceThere(int direction);

  };

}
