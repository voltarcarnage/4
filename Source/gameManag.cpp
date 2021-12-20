#include "headers/gameManag.h"

namespace Game_N{

  GameManager::GameManager(): hero_(),window_(sf::VideoMode(1000, 1000), "Necromancer"),hud_()
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
    UP_ = false; DOWN_ = false; LEFT_ = false; RIGHT_ = false; Z_ = false; X_ = false; C_ = false; V_ = false; INTERACT_ = false; YES_ = false; NO_ = false;
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
    hud_.drawHUD(window_,hero_);
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
    if(key == sf::Keyboard::Z)
        Z_ = pressed;
    if(key == sf::Keyboard::X)
        X_ = pressed;
    if(key == sf::Keyboard::C)
        C_ = pressed;
    if(key == sf::Keyboard::V)
        V_ = pressed;
    if(key == sf::Keyboard::E)
        INTERACT_ = pressed;
    if(key == sf::Keyboard::Y)
        YES_ = pressed;
    if(key == sf::Keyboard::N)
        NO_ = pressed;
  }

  void GameManager::interactionWithMap()
  {
    for(auto & i : levels_[level_].getCell())//map
        for(auto & j : i)
        {
          if(j.getCellType() == 0)
          {
            if(hero_.getShape().getGlobalBounds().intersects(j.getRectangle().getGlobalBounds()))
            {
              if(UP_)
              {
                sf::Vector2f vec;
                vec = hero_.getCoords();
                vec.y += 5 * hero_.getSpeed();
                hero_.setCoords(vec);
              }
              else if(DOWN_)
              {
                sf::Vector2f vec;
                vec = hero_.getCoords();
                vec.y -= 5 * hero_.getSpeed();
                hero_.setCoords(vec);
              }
              else if(RIGHT_)
              {
                sf::Vector2f vec;
                vec = hero_.getCoords();
                vec.x -= 5 * hero_.getSpeed();
                hero_.setCoords(vec);
              }
              else if(LEFT_)
              {
                sf::Vector2f vec;
                vec = hero_.getCoords();
                vec.x += 5 * hero_.getSpeed();
                hero_.setCoords(vec);
              }
            }
          }
          else if(j.getCellType() == 2)
          {
            if(hero_.getShape().getGlobalBounds().intersects(j.getRectangle().getGlobalBounds()))
            {
              hero_.takeDamage(1);
            }
          }

        }
  }

  void GameManager::heroCombat()
  {
    for(int i = 0; i < levels_[level_].getEnemies().size(); i++)
    {
      if(hero_.detectEnemy(levels_[level_].getEnemies()[i].getCell().getRectangle().getPosition()))
      {
        if(Z_)
          if(!levels_[level_].getEnemies()[i].takeDamage(30))
            levels_[level_].getEnemies()[i].die();
      }
    }
  }

  void GameManager::updateEnemy(sf::Time dt)
  {
    for(auto & i : levels_[level_].getEnemies()) {
        if(i.isAlive()){
        sf::Vector2f tmp = i.getCell().getRectangle().getPosition();
        if ((levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x + 100.f, i.getCell().getRectangle().getPosition().y}) > 0//up
             && levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x  , i.getCell().getRectangle().getPosition().y}) > 0)
            &&
            (levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x , i.getCell().getRectangle().getPosition().y + 100.f}) > 0//down
             && levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x + 100.f , i.getCell().getRectangle().getPosition().y + 100.f}) > 0)
            &&
            (levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x , i.getCell().getRectangle().getPosition().y}) > 0//left
             && levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x , i.getCell().getRectangle().getPosition().y + 100.f}) > 0)
            &&
            (levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x + 100.f , i.getCell().getRectangle().getPosition().y}) > 0//right
             && levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x + 100.f , i.getCell().getRectangle().getPosition().y + 100.f}) > 0))
            i.move(hero_.getCoords());

        else {
            bool up_left = levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x, i.getCell().getRectangle().getPosition().y}) == 0;//up_left

            bool down_left = levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x, i.getCell().getRectangle().getPosition().y + 100.f}) == 0;//down_left


            bool up_right = levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x + 100.f, i.getCell().getRectangle().getPosition().y}) == 0;//up_right


            bool down_right = levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x + 100.f , i.getCell().getRectangle().getPosition().y + 100.f}) == 0;//down_right


            if(up_left) {
                tmp.y += 1.f;
                tmp.x += 1.f;
            }
            if(down_left) {
                tmp.y -= 1.f;
                tmp.x += 1.f;
            }
            if(up_right) {
                tmp.x -= 1.f;
                tmp.y += 1.f;
            }
            if(down_right) {
                tmp.x -= 1.f;
                tmp.y -= 1.f;
            }
            if(up_left && up_right){
                tmp.y += 1.f;
            }
            if(up_left && down_left){
                tmp.x += 1.f;
            }
            if(up_right && down_right){
                tmp.x -= 1.f;
            }
            if(down_left && down_right){
                tmp.y -= 1.f;
            }
            i.move(tmp);
        }
    for (int i = 0; i < levels_[level_].getEnemies().size(); i++) {
        if (sqrt(pow(levels_[level_].getEnemies()[i].getCell().getRectangle().getPosition().x - hero_.getShape().getPosition().x, 2) +
        pow(levels_[level_].getEnemies()[i].getCell().getRectangle().getPosition().y - hero_.getShape().getPosition().y, 2)) <= 100.f) {
            sf::Time time = levels_[level_].getEnemies()[i].getClock();
                if(time.asSeconds() >= sf::seconds(2.f).asSeconds()) {
                    hero_.takeDamage(levels_[level_].getEnemies()[i].getDamage());
                    levels_[level_].getEnemies()[i].restartClock();
                    break;
                  }
              }
            }
      }
    }
  }

  void GameManager::moveHero()
  {
    if(UP_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.y -= hero_.getSpeed();
      hero_.setCoords(vec);
    }
    else if(DOWN_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.y += hero_.getSpeed();
      hero_.setCoords(vec);
    }
    else if(RIGHT_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.x += hero_.getSpeed();
      hero_.setCoords(vec);
    }
    else if(LEFT_)
    {
      sf::Vector2f vec;
      vec = hero_.getCoords();
      vec.x -= hero_.getSpeed();
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
        interactionWithMap();
        moveHero();
        heroCombat();
        // moveEnemy();
        updateEnemy(time);
        // update_player(time);
        update();
    }
  }


}
