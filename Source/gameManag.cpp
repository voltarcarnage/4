#include "headers/gameManag.h"

namespace Game_N{

  GameManager::GameManager(): hero_(),window_(sf::VideoMode(1000, 1000), "Necromancer") /*, hud(&this->prowler.get_characteristics())*/
  {
    int name = 1;
    std::ifstream file;
    while(true)
    {
      file.open("level/" + std::to_string(name) + ".txt");
      if(file.is_open())
      {
        levels_.emplace_back(name);
        name++;
        file.close();
      }
      else
        break;
    }
    UP_ = false; DOWN_ = false; LEFT_ = false; RIGHT_ = false; HIT_ = false; INTERACT_ = false;
    level_ = 0;
    hero_.setCoords(levels_[level_].getHeroCoord());
  }

  void GameManager::update()
  {
    window_.clear();
    for(auto & i : levels_[level_].getCell())//map
        for(auto & j : i){
           window_.draw(j.getRectangle());
       }
    for(auto & i : levels_[level_].getEnemies()) {//enemies
        window_.draw(i.getCell().getRectangle());
        // window.draw(i.get_info().get_max_hp());
        // window.draw(i.get_info().get_cur_hp());
    }

    window_.draw(hero_.getShape());//player

    window_.display();
  }

  void GameManager::chooseEvent()
  {
    sf::Event event;
    while(window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window_.close();
                break;
            case sf::Event::KeyPressed:
                input(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                input(event.key.code, false);
            default:
                continue;
        }
    }
  }

  void GameManager::input(sf::Keyboard::Key key, bool pressed)
  {
    if(key == sf::Keyboard::W)
        UP_ = pressed;
    if(key == sf::Keyboard::A)
        LEFT_ = pressed;
    if(key == sf::Keyboard::S)
        DOWN_ = pressed;
    if(key == sf::Keyboard::D)
        RIGHT_ = pressed;
    if(key == sf::Keyboard::H)
        HIT_ = pressed;
    if(key == sf::Keyboard::I)
        INTERACT_ = pressed;
    if(key == sf::Keyboard::Num1)
        NUM1_ = pressed;
    if(key == sf::Keyboard::Num2)
        NUM2_ = pressed;
  }

  void GameManager::interactionWithMap()
  {

  }

  void GameManager::moveHero()
  {
    if(UP_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.y--;
      hero_.setCoords(vec);
    }
    else if(DOWN_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.y++;
      hero_.setCoords(vec);
    }
    else if(RIGHT_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.x++;
      hero_.setCoords(vec);
    }
    else if(LEFT_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.x--;
      hero_.setCoords(vec);
    }
  }

  void GameManager::start()
  {
    sf::Time time = sf::seconds(1.f / 60.f);
    window_.setFramerateLimit(60);
    while(window_.isOpen() && hero_.isAlive())
    {
        chooseEvent();
        moveHero();
        // update_enemy(time);
        // update_player(time);
        update();
    }
  }


}
