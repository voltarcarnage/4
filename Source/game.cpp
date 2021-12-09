#include "headers/game.h"

namespace Game_N{

  void Game::Start()
  {
    if(status_ != Begin){
      return;
    }

    gameWindow_.create(sf::VideoMode(WIDTH_, HEIGHT_), "Necromancer");
    status_ = Play;

    while(gameWindow_.isOpen()){
      Loop();
    }
  }

  sf::RenderWindow& Game::getWindow()
  {
	   return gameWindow_;
  }

  void Game::Loop()
  {
    sf::Event event;

    gameWindow_.clear();

    while(gameWindow_.pollEvent(event)){
		  if(event.type == sf::Event::Closed)
			   gameWindow_.close();
	   }

    switch(status_)
    {
      // case Play:{
      //   if(manager_.gameOn())
      //   {
      //     manager_.updateAll(gameWindow_);
			// 		manager_.drawAll(gameWindow_);
      //
      //     gameWindow_.display();
      //   }
      //   else
      //   {
      //     status_ = Exit;
      //   }
      //
      //   break;
      // }

      case Exit:{
        endGame();
        gameWindow_.display();

        break;
      }

    }
  }

  void Game::endGame()
  {
    while(gameWindow_.isOpen()){
      sf::Event event;
      gameWindow_.clear();

      while(gameWindow_.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				gameWindow_.close();
      }
    }
  }


}
