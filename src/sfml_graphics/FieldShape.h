#ifndef FIELD_SHAPE_H
#define FIELD_SHAPE_H

#include <SFML/Graphics.hpp>

class FieldShape : public sf::Drawable {
public:
    FieldShape(const int fieldSize);
    FieldShape(const int fieldSize, const float cellWidth);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Texture _fieldTexture;
};

#endif