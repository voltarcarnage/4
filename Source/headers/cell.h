#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>

#pragma once

namespace Game_N{

  class Cell {
    private:
        sf::RectangleShape rectangle_;
        sf::Vector2f coord_;
        int cell_;
    public:
        Cell();
        Cell(sf::Vector2f coords, int cell, sf::Color color);
        sf::Vector2f getCoords(){ return rectangle_.getPosition(); };
        sf::RectangleShape& getRectangle(){ return rectangle_; };
        int getCellType() const { return cell_; };
        void setCell(int ch){ cell_ = ch; };
        void setCoords(sf::Vector2f coords){ rectangle_.setPosition(coords); };
  };

}
