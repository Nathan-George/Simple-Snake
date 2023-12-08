#include "LineShape.h"

#include <cmath>

LineShape::LineShape(std::vector<sf::Vector2f> points, float radius) : _points(points), _radius(radius) {}

void LineShape::setColor(sf::Color color) {
    _color = color;
}

void LineShape::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    sf::ConvexShape segment(4);
    segment.setFillColor(_color);
    for (size_t i = 1; i < _points.size(); i++) {

        sf::Vector2f vec = _points.at(i) - _points.at(i-1);
        float dir = std::atan2(vec.y, vec.x);

        // could be problematic
        float theta = std::acos(0);

        segment.setPoint( 0, _points.at(i) + _radius * sf::Vector2f(std::cos(dir + theta), std::sin(dir + theta)) );
        segment.setPoint( 1, _points.at(i-1) + _radius * sf::Vector2f(std::cos(dir + theta), std::sin(dir + theta)) );
        segment.setPoint( 2, _points.at(i-1) + _radius * sf::Vector2f(std::cos(dir - theta), std::sin(dir - theta)) );
        segment.setPoint( 3, _points.at(i) + _radius * sf::Vector2f(std::cos(dir - theta), std::sin(dir - theta)) );

        target.draw(segment, states);
    }

    sf::CircleShape corner(_radius);
    corner.setFillColor(_color);
    for (size_t i = 0; i < _points.size(); i++) {
        corner.setPosition(_points.at(i) - sf::Vector2f(_radius, _radius));
        target.draw(corner, states);
    }
}
