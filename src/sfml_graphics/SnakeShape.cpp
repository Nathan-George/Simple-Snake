
#include "SnakeShape.h"
#include "LineShape.h"

#include <stdexcept>
#include <iostream>

#include <cmath>

SnakeShape::SnakeShape(const Snake& snake, const int fieldSize) : SnakeShape(snake, fieldSize, 40) {}

SnakeShape::SnakeShape(const Snake& snake, const int fieldSize, const float cellWidth) : 
    _pSnake(&snake), 
    _fieldSize(fieldSize), 
    _cellWidth(cellWidth) {}

void SnakeShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RenderTexture renderTexture;

    const unsigned int textureSize = static_cast<unsigned int>(_fieldSize * _cellWidth);
    if (!renderTexture.create(textureSize, textureSize)) {
        throw std::runtime_error("Could not create snake texture");
    }

    renderTexture.clear(sf::Color(0,0,0,0));
    renderTexture.setSmooth(true);

    std::vector<sf::Vector2f> points(_pSnake->length());
    for (size_t i = 0; i < _pSnake->length(); i++) {
        Location location = _pSnake->getLocationAt(i);
        points.at(i) = (sf::Vector2f(location.x, location.y) + sf::Vector2f(0.5, 0.5)) * _cellWidth;
    }

    LineShape snakeLine(points, _cellWidth * 0.25);
    snakeLine.setColor(sf::Color(63, 63, 255));
    renderTexture.draw(snakeLine, states);

    // head
    Location head = _pSnake->getHead();
    sf::Vector2f headVector(head.x, head.y);
    headVector = (headVector + sf::Vector2f(0.5, 0.5)) * _cellWidth;

    sf::Vector2f dir(0, 1);
    if (_pSnake->length() >= 2) {
        dir.x = head.x - _pSnake->getLocationAt(1).x;
        dir.y = head.y - _pSnake->getLocationAt(1).y;
    }
    float theta = std::atan2(dir.y, dir.x);

    sf::CircleShape eye;
    eye.setFillColor(sf::Color(63, 63, 255));
    eye.setRadius(0.15 * _cellWidth);
    eye.setPosition(headVector + 0.25f * sf::Vector2f(cos(theta + 2.5), sin(theta + 2.5)) * _cellWidth - sf::Vector2f(eye.getRadius(), eye.getRadius()));
    renderTexture.draw(eye);
    eye.setFillColor(sf::Color::White);
    eye.setRadius(0.08 * _cellWidth);
    eye.setPosition(headVector + 0.25f * sf::Vector2f(cos(theta + 2.5), sin(theta + 2.5)) * _cellWidth - sf::Vector2f(eye.getRadius(), eye.getRadius()));
    renderTexture.draw(eye);
    eye.setFillColor(sf::Color::Black);
    eye.setRadius(0.04 * _cellWidth);
    eye.setPosition(headVector + 0.25f * sf::Vector2f(cos(theta + 2.5), sin(theta + 2.5)) * _cellWidth + 0.03f * dir * _cellWidth - sf::Vector2f(eye.getRadius(), eye.getRadius()));
    renderTexture.draw(eye);
    eye.setFillColor(sf::Color(63, 63, 255));
    eye.setRadius(0.15 * _cellWidth);
    eye.setPosition(headVector + 0.25f * sf::Vector2f(cos(theta - 2.5), sin(theta - 2.5)) * _cellWidth - sf::Vector2f(eye.getRadius(), eye.getRadius()));
    renderTexture.draw(eye);
    eye.setFillColor(sf::Color::White);
    eye.setRadius(0.08 * _cellWidth);
    eye.setPosition(headVector + 0.25f * sf::Vector2f(cos(theta - 2.5), sin(theta - 2.5)) * _cellWidth - sf::Vector2f(eye.getRadius(), eye.getRadius()));
    renderTexture.draw(eye);
    eye.setFillColor(sf::Color::Black);
    eye.setRadius(0.04 * _cellWidth);
    eye.setPosition(headVector + 0.25f * sf::Vector2f(cos(theta - 2.5), sin(theta - 2.5)) * _cellWidth + 0.03f * dir * _cellWidth - sf::Vector2f(eye.getRadius(), eye.getRadius()));
    renderTexture.draw(eye);


    sf::Texture snakeTexture;
    if (!snakeTexture.create(textureSize, textureSize)) {
        throw std::runtime_error("Could not create snake texture");
    }

    snakeTexture.update(renderTexture.getTexture());
    snakeTexture.setSmooth(true);


    sf::Sprite snakeSprite(snakeTexture);

    target.draw(snakeSprite, states);
}