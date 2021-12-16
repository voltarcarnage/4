#include "headers/cell.h"

namespace Game_N{

  Cell::Cell()
  {
    coord_ = {0, 0};
    rectangle_ = sf::RectangleShape(sf::Vector2f(40, 40));
    rectangle_.setFillColor(sf::Color::Blue);
    cell_ = 0;
  }

  Cell::Cell(sf::Vector2f coords, int cell, sf::Color color)
  {
    // this->rect.setOutlineColor(sf::Color::Green);
    rectangle_ = sf::RectangleShape(sf::Vector2f(100, 100));
    rectangle_.setFillColor(color);
    rectangle_.setPosition(coords.x * 100, coords.y * 100);
    // coord_.x *= 100;
    // coord_.y *= 100;
    cell_ = cell;
  }

}
