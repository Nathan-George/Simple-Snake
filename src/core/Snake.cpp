
#include "Snake.h"

#include <stdexcept>

Snake::Snake(ISnakeBehavior* const pBehavior, Field& field) : Snake(pBehavior, field, Location()) {}
Snake::Snake(ISnakeBehavior* const pBehavior, Field& field, Location headNode) : Snake(pBehavior, field, std::vector<Location>{headNode}) {}
Snake::Snake(ISnakeBehavior* const pBehavior, Field& field, const std::vector<Location> &nodes) : _pBehavior(pBehavior), _nodes() {

    int i = 0;
    for (Location location : nodes) {
        _nodes.push_back(location);

        // update field
        field.at(location) = FieldCell(i++);
    }
}

Move Snake::move(Field& field, const Apple& apple) {
    const Move move = _pBehavior->getMove(*this, field, apple);
    int dx(0), dy(0);

    switch (move) {
    case Move::Right:
        dx=1;
        break;
    case Move::Up:
        dy=1;
        break;
    case Move::Left:
        dx=-1;
        break;
    case Move::Down:
        dy=-1;
        break;
    
    default:
        break;
    }

    Location moveLocation = Location(getHead().x + dx, getHead().y + dy);

    // check for illegal moves
    if (!field.inField(moveLocation)) {
        throw std::runtime_error("Illegal move! Snake tried to move off of the field");
    }

    // remove tail
    if (moveLocation != apple.getLocation()) {
        field.at(getTail()) = FieldCell(); // empty cell
        _nodes.pop_back();
    }

    if (field.at(moveLocation).isSnakeNode()) {
        throw std::runtime_error("Illegal move! Snake tried to move into itself");
    }

    // increment indexes of the field cells
    int i = 0;
    for (Location location : _nodes) {
        field.at(location).updateIndex(++i);
    }

    // add new cell
    _nodes.push_front(moveLocation);
    field.at(getHead()) = FieldCell(0); // head cell

    return move;
}

Location Snake::getLocationAt(int index) const {
    // TODO: bounds check

    return _nodes.at(index);
}

unsigned int Snake::length() const {
    return _nodes.size();
}
Location Snake::getHead() const {
    return _nodes.front();
}
Location Snake::getTail() const {
    return _nodes.back();
}
