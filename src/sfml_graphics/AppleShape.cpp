
#include "AppleShape.h"

#include <stdexcept>

AppleShape::AppleShape(const int fieldSize, const float cellWidth) : _cellWidth(cellWidth), _fieldSize(fieldSize) {
    _location = sf::Vector2f(0, 0);

    const unsigned int textureSize = static_cast<unsigned int>(cellWidth);

    if (!_appleTexture.create(textureSize, textureSize)) {
        throw std::runtime_error("Could not create apple texture");
    }

    sf::CircleShape circle(0.333 * cellWidth);
    circle.setFillColor(sf::Color(200, 63, 63));
    circle.setPosition(sf::Vector2f(0.5, 0.5) * cellWidth - sf::Vector2f(circle.getRadius(), circle.getRadius()));

    _appleTexture.draw(circle);
}

void AppleShape::setLocation(const Location location) {
    _location = sf::Vector2f(location.x, _fieldSize-1 - location.y) * _cellWidth;
}

void AppleShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite appleSprite(_appleTexture.getTexture());

    appleSprite.setPosition(_location);

    target.draw(appleSprite, states);
}