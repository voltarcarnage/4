#include "headers/lvl.h"

namespace Game_N{

    Level::Level(){}

    Level::Level(int num)
    {
      std::ifstream file("level/" + std::to_string(num) + ".txt");
      std::string str;
      int y = 0;
      if(file.is_open()){
          while(getline(file, str)){
              mapStr_ += str;
              std::vector<Cell> cell;
              for(int x = 0; x < str.size(); ++x){
                  switch(str[x]){
                      case '#': {//wall
                          Cell c(sf::Vector2f(x, y), 0, sf::Color::Cyan);
                          cell.push_back(c);
                          break;
                      }
                      case '.':{//void
                          Cell c(sf::Vector2f(x, y), 1,sf::Color::Green);
                          cell.push_back(c);
                          break;
                      }
                      case 'l':{//lava
                          Cell c(sf::Vector2f(x,y), 2,sf::Color::Yellow);
                          cell.push_back(c);
                          break;
                      }
                      case '@':{//hero
                          Cell c(sf::Vector2f(x, y), 3,sf::Color::Green);
                          cell.push_back(c);
                          break;
                      }
                      case 'i':{//in
                          Cell c(sf::Vector2f(x, y), 4,sf::Color::Cyan);
                          cell.push_back(c);
                          break;
                      }
                      case 'o':{//out
                          Cell c(sf::Vector2f(x, y), 5,sf::Color::Transparent);
                          cell.push_back(c);
                          break;
                      }
                      case 'z':{//enemy
                        Cell c(sf::Vector2f(x, y), 1, sf::Color(0, 255, 0));
                        enemies_.emplace_back(1,2,10, "ork", sf::Vector2f(x, y));
                        cell.push_back(c);
                        break;
                      }
                      default:
                          continue;
                  }
              }
              mapCell_.push_back(cell);
              y++;
            }
        }
  }

  Level::Level(const Level& i)
  {
    enemies_ = i.enemies_;
    mapCell_ = i.mapCell_;
    mapStr_ = i.mapStr_;
  }

  int Level::getTileType(sf::Vector2f coords)
  {
    int x = static_cast<int>(coords.x) / 100;
    int y = static_cast<int>(coords.y) / 100;
    return mapCell_[y][x].getCell();
  }

  sf::Vector2f Level::getHeroCoord()
  {
    for(int i = 0; i < mapCell_.size(); i++)
      for(int j = 0; j < mapCell_[i].size(); j++)
        if(mapStr_[i * mapCell_.size() + j] == '@')
          return {j * 100.f, i * 100.f};
  }

}
