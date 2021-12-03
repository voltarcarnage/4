#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <regex>

#include "gameManage.h"

#pragma once

namespace Game_N{

  class Game{
    private:
      enum GameStatus {Begin, Menu, Play, Exit};
      GameStatus status_;
      void Loop();
      sf::RenderWindow gameWindow_;
      void showMenu();
      void endGame();
      GameManager manager_;
    public:
      void Start();
      sf::RenderWindow& getWindow();

      const int WIDTH_ = 800;
	    const int HEIGHT_ = 600;
  };

}
