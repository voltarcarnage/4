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
    getExp_ = false;
    UP_ = false; DOWN_ = false; LEFT_ = false; RIGHT_ = false; Z_ = false; X_ = false; C_ = false; V_ = false; INTERACT_ = false; HP_ = false; MANA_ = false;
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
        window_.draw(i.getText());
    }

    for(int i = 0; i < hero_.getUndeads().size(); i++)
    {
      window_.draw(hero_.getUndeads()[i].getCell().getRectangle());
      window_.draw(hero_.getUndeads()[i].getText());
    }

    window_.draw(hero_.getShape());//player
    hud_.drawHUD(window_,hero_);
    window_.setKeyRepeatEnabled(false);
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
    if(key == sf::Keyboard::H)
        HP_ = pressed;
    if(key == sf::Keyboard::M)
        MANA_ = pressed;
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
      sf::Vector2f vect = levels_[level_].getEnemies()[i].getCell().getRectangle().getPosition();
      if(hero_.detectEnemy(vect) && hero_.getMana() > 0)
      {
        if(Z_)
        {
          hero_.decreaseMana(hero_.getSpell("curse",vect)->getManaCost());
          if(!levels_[level_].getEnemies()[i].takeDamage(hero_.getSpell("curse",vect)->getDmgBySpell()))
          {
            levels_[level_].getEnemies()[i].die();
            if(levels_[level_].getEnemies()[i].getState()){
              auto iter = levels_[level_].getEnemies().cbegin();
              levels_[level_].getEnemies().erase(iter + i);
            }
            getExp_ = true;
          }
          Z_ = false;
        }
        else if(X_)
        {
          if(!levels_[level_].getEnemies()[i].isAlive())
          {
            if(HP_)
            {
              hero_.castASpell("desiccationH",levels_[level_].getEnemies()[i]);
              auto iter = levels_[level_].getEnemies().cbegin();
              levels_[level_].getEnemies().erase(iter + i);
            }
            else if(MANA_)
            {
              hero_.castASpell("desiccationM",levels_[level_].getEnemies()[i]);
              auto iter = levels_[level_].getEnemies().cbegin();
              levels_[level_].getEnemies().erase(iter + i);
            }
          }
        }
        else if(C_)
        {
          if(!levels_[level_].getEnemies()[i].isAlive())
          {
            if(hero_.getUndeads().size() <= hero_.getUndeadsCount()){
            hero_.castASpell("necromancy", levels_[level_].getEnemies()[i]);
            auto iter = levels_[level_].getEnemies().cbegin();
            levels_[level_].getEnemies().erase(iter + i);
            }
          }
          C_ = false;
        }
      }

      if(!levels_[level_].getEnemies()[i].isAlive() && getExp_)
      {
        getExp_ = false;
        hero_.gainExp(20);
      }
    }

    for(int i = 0; i < hero_.getUndeads().size(); i++)
    {
      if(V_)
      {
        hero_.castASpell("morphism",hero_.getUndeads()[i]);
        V_ = false;
      }
    }

  }

  void GameManager::updateUndeads(sf::Time dt)
  {
    int quot = 0;
    for(auto & i : hero_.getUndeads()) {
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
             && levels_[level_].getTileType({i.getCell().getRectangle().getPosition().x + 100.f , i.getCell().getRectangle().getPosition().y + 100.f}) > 0)){
               for(auto & j : levels_[level_].getEnemies())
               {
                 if(j.isAlive())
                  i.move(j.getCell().getRectangle().getPosition());
                else
                {
                  ++quot;
                  if(!(quot % 2)){
                    i.move(hero_.getCoords() + sf::Vector2f(quot * 0.45 * pow(-1, quot + 1) * 70.f,85.f));
                    continue;
                  }
                  else
                    i.move(hero_.getCoords() + sf::Vector2f(quot * 0.45 * pow(-1, quot + 1) * 70.f,quot * 0.45 * pow(-1, quot + 1) * 85.f));
                }
               }

               if(levels_[level_].getEnemies().empty()){
                  ++quot;
                 if(!(quot % 2)){
                   i.move(hero_.getCoords() + sf::Vector2f(quot * 0.45 * pow(-1, quot + 1) * 70.f,85.f));
                  continue;
                 }
                 else
                   i.move(hero_.getCoords() + sf::Vector2f(quot * 0.45 * pow(-1, quot + 1) * 70.f,quot * 0.45 * pow(-1, quot + 1) * 85.f));
              }
             }

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

    for(int i = 0; i < hero_.getUndeads().size(); i++) {
      for(int j = 0; j < levels_[level_].getEnemies().size(); j++){
        if (sqrt(pow(hero_.getUndeads()[i].getCell().getRectangle().getPosition().x - levels_[level_].getEnemies()[j].getCell().getRectangle().getPosition().x, 2) +
        pow(hero_.getUndeads()[i].getCell().getRectangle().getPosition().y - levels_[level_].getEnemies()[j].getCell().getRectangle().getPosition().y, 2)) <= 100.f) {
          sf::Time time = hero_.getUndeads()[i].getClock();
          if(time.asSeconds() >= sf::seconds(1.f).asSeconds()) {
            if(levels_[level_].getEnemies()[j].isAlive()){
              if(!levels_[level_].getEnemies()[j].takeDamage(hero_.getUndeads()[i].getDamage())){
                levels_[level_].getEnemies()[j].die();
                getExp_ = true;
                }
              }
              if(!levels_[level_].getEnemies()[j].isAlive() && getExp_)
              {
                getExp_ = false;
                hero_.gainExp(20);
              }
              hero_.getUndeads()[i].restartClock();
              break;
            }
          }
        }
      }

      i.getFont().loadFromFile("resources/ShareTech.ttf");

      i.getText().setFont(i.getFont());
      i.getText().setCharacterSize(25);
      i.getText().setColor(sf::Color::Black);

      i.getText().setString(i.getName());
      i.getText().setPosition(i.getCell().getRectangle().getPosition().x, i.getCell().getRectangle().getPosition().y + 25);

    }
  }
}

  void GameManager::updateEnemy(sf::Time dt)
  {
    int k = 0;
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
        if(levels_[level_].getEnemies()[i].getName() == "summoner")
        {
          k = i;
          continue;
        }
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
  if (sqrt(pow(levels_[level_].getEnemies()[k].getCell().getRectangle().getPosition().x - hero_.getShape().getPosition().x, 2) +
                pow(levels_[level_].getEnemies()[k].getCell().getRectangle().getPosition().y - hero_.getShape().getPosition().y, 2)) <= 500.f) {
                    sf::Time time = levels_[level_].getEnemies()[k].getClock();
                        if(time.asSeconds() >= sf::seconds(5.f).asSeconds()) {
                            Enemy summoned(levels_[level_].getEnemies()[k].getLvl(),2,5, true, "summoned", sf::Vector2f(levels_[level_].getEnemies()[k].getCell().getRectangle().getPosition().x, levels_[level_].getEnemies()[k].getCell().getRectangle().getPosition().y),sf::Color(100,100,100));
                            // levels_[level_].addCell(summoned.getCell());
                            // std::cout << summoned.getCell().getRectangle().getPosition().x << std::endl;
                            levels_[level_].addEnemy(summoned);
                            hero_.takeDamage(levels_[level_].getEnemies()[k].getDamage());
                            levels_[level_].getEnemies()[k].restartClock();
                            // break;
                          }
                      }
      }

                  i.getFont().loadFromFile("resources/ShareTech.ttf");

                	i.getText().setFont(i.getFont());
                	i.getText().setCharacterSize(25);
                	i.getText().setColor(sf::Color::Black);

                  i.getText().setString(i.getName());
                  i.getText().setPosition(i.getCell().getRectangle().getPosition().x, i.getCell().getRectangle().getPosition().y + 25);
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
        updateEnemy(time);
        heroCombat();
        // moveEnemy();
        updateUndeads(time);
        update();
        // update_player(time);
    }
  }


}
