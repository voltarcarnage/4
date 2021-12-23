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
                      case '+':{//in
                          Cell c(sf::Vector2f(x, y), 4,sf::Color::Cyan);
                          cell.push_back(c);
                          break;
                      }
                      case '-':{//out
                          Cell c(sf::Vector2f(x, y), 5,sf::Color::Transparent);
                          cell.push_back(c);
                          break;
                      }
                      case 'g':{//ghoul
                        Cell c(sf::Vector2f(x, y), 6, sf::Color(2, 255, 0));
                        enemies_.emplace_back(num,3,14, false,"ghoul", sf::Vector2f(x, y),sf::Color(255,73,108));
                        cell.push_back(c);
                        break;
                      }
                      case 'o':{//ork
                        Cell c(sf::Vector2f(x, y), 7, sf::Color(2, 255, 0));
                        enemies_.emplace_back(num,2,10, false, "ork", sf::Vector2f(x, y),sf::Color(255,180,231));
                        cell.push_back(c);
                        break;
                      }
                      case 's':{//skeleton
                        Cell c(sf::Vector2f(x, y), 7, sf::Color(2, 255, 0));
                        enemies_.emplace_back(num,5,15, false, "skeleton", sf::Vector2f(x, y),sf::Color(125,127,125));
                        cell.push_back(c);
                        break;
                      }
                      case 'z':{//zombie
                        Cell c(sf::Vector2f(x, y), 8, sf::Color(2, 255, 0));
                        enemies_.emplace_back(num,2,17, true, "zombie", sf::Vector2f(x, y),sf::Color(178,236,93));
                        cell.push_back(c);
                        break;
                      }
                      case 'S':{//summoner
                        Cell c(sf::Vector2f(x, y), 9, sf::Color(2, 255, 0));
                        enemies_.emplace_back(num,2,8, false, "summoner", sf::Vector2f(x, y),sf::Color(148,0,211));
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
    return mapCell_[y][x].getCellType();
  }

  sf::Vector2f Level::getHeroCoord()
  {
    for(int i = 0; i < mapCell_.size(); i++)
      for(int j = 0; j < mapCell_[i].size(); j++)
        if(mapStr_[i * mapCell_.size() + j] == '@')
          return {j * 110.f, i * 110.f};
  }

}
