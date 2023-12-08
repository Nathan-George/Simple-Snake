
#include "FieldShape.h"

#include <stdexcept>

FieldShape::FieldShape(const int fieldSize) : FieldShape(fieldSize, 40.0) {}

FieldShape::FieldShape(const int fieldSize, const float cellWidth) {
    sf::RenderTexture fieldTexture;

    const unsigned int textureSize = static_cast<unsigned int>(fieldSize * cellWidth);
    if (!fieldTexture.create(textureSize, textureSize)) {
        throw std::runtime_error("Could not create field texture");
    }

    for (int i = 0; i < fieldSize; i++) {
        for (int j = 0; j < fieldSize; j++) {
            sf::RectangleShape tile(sf::Vector2f(cellWidth, cellWidth));
            tile.setPosition(i * cellWidth, j * cellWidth);

            // color
            if ((i + j) % 2 == 0) tile.setFillColor(sf::Color(63, 190, 63));
            else tile.setFillColor(sf::Color(79, 206, 79));

            fieldTexture.draw(tile);
        }
    }

    // update the contents
    fieldTexture.display();
    _fieldTexture = fieldTexture.getTexture();
}

void FieldShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sf::Sprite(_fieldTexture), states);
}