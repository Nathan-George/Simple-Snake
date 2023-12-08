#ifndef LINE_SHAPE_H
#define LINE_SHAPE_H

#include <SFML/Graphics.hpp>

#include <vector>

class LineShape : public sf::Drawable {
public:
    LineShape(std::vector<sf::Vector2f> points, float radius);

    void setColor(sf::Color color);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    std::vector<sf::Vector2f> _points;
    float _radius;

    sf::Color _color;
};

#endif