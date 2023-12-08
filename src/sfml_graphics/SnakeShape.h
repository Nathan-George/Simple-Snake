#ifndef SNAKE_SHAPE_H
#define SNAKE_SHAPE_H

#include "../core/Snake.h"

#include <SFML/Graphics.hpp>

class SnakeShape : public sf::Drawable {
public:
    SnakeShape(const Snake& snake, const int fieldSize);
    SnakeShape(const Snake& snake, const int fieldSize, const float cellWidth);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    const Snake* const _pSnake;

    const int _fieldSize;
    const float _cellWidth;
};

#endif