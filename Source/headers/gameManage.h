#include <SFML/Graphics.hpp>
// #include <stdlib.h>
// #include <stdio.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
// #include <utility>
// #include "HUD.hpp"

#include "enemy.h"
#include "hero.h"

#pragma once

namespace Game_N{

  class GameManager{
    private:
      bool gameOn_;
      void newLvl();
      void nextLevel(sf::RenderWindow& window);
    	int dungeonLevel_;
    	void addMonsters();
    	void setEnemies();

    	void loadEnemyTexture(Enemy& enemy);

    	void enemyTurn();

      std::vector<std::vector<int>> makeMap(int a);
    	void findStart(std::vector<std::vector<int>> map);
    	void movePlayer(int a);
    	void updatePercentages();
    	void drawMap(sf::RenderWindow& window);
    	void drawMC(sf::RenderWindow& window);
    	void drawEnemies(sf::RenderWindow& window);
    	Hero hero;
    	// HUD hud; Add hud
    	bool movingUp_,movingDown_,movingLeft_,movingRight_,heroMadeMove_;
    	bool fighting_;
    	int n_,m_,mapSize_;
    	float animationTime_,cmdTime_,yPercentage_,xPercentage_,movePercentage_,offsetY_,offsetX_;
    	sf::Clock clock_;
    	sf::Vector2i MCspot_;
    	std::vector<Monster> availableMonsters_;
    	std::vector<Monster> monsters_;

      sf::Texture wallT_;
    	sf::Texture groundT_;
    	sf::Texture MCt_;
    	sf::Texture stairsT_;
    	std::map<std::string,sf::Texture> enemyTextures_;

    	sf::Sprite wall_;
    	sf::Sprite ground_;
    	sf::Sprite MC_;
    	sf::Sprite stairs_;
    	std::map<std::string,sf::Sprite> enemySprites_;

    	sf::IntRect SourceSprite_;
    	std::vector<std::vector<int>> map;
    public:
      GameManager();
    	void updateAll(sf::RenderWindow& window);
    	void drawAll(sf::RenderWindow & window);

    	bool isFreeTile(unsigned int x, unsigned int y);
    	bool freeLineOfSight(sf::Vector2i a, sf::Vector2i b);
    	bool hearPlayer(Enemy& enemy);
    	bool seePlayer(Enemy& enemy);
    	bool gameOn();
    	void tryDetectPlayer(Enemy& enemy);
  };

}
