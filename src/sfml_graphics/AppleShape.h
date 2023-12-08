#ifndef APPLE_SHAPE_H
#define APPLE_SHAPE_H

#include "../core/Location.h"

#include <SFML/Graphics.hpp>

class AppleShape : public sf::Drawable {
public:
    AppleShape(const int fieldSize, const float cellWidth);

    void setLocation(const Location location);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::RenderTexture _appleTexture;
    sf::Vector2f _location;

    const float _cellWidth;
    const int _fieldSize;
};

#endif