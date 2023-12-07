
#include "Field.h"

FieldCell::FieldCell() {
    _isSnakeNode = false;
    _snakeNodeIndex = -1;
}
FieldCell::FieldCell(int index) {
    _isSnakeNode = true;
    _snakeNodeIndex = index;
}

bool FieldCell::isEmpty() const {
    return !_isSnakeNode;
}
bool FieldCell::isSnakeNode() const {
    return _isSnakeNode;
}

void FieldCell::updateIndex(int index) {
    _snakeNodeIndex = index;
}

int FieldCell::index() const {
    return _snakeNodeIndex;
}

int FieldCell::indexOr(int value) const {
    return isSnakeNode() ? _snakeNodeIndex : value;
}

Field::Field(int size) : _field(size, std::vector<FieldCell>(size, FieldCell())), _size(size) {}

const FieldCell& Field::at(Location location) const {
    return _field.at(location.y).at(location.x);
}
FieldCell& Field::at(Location location) {
    return _field.at(location.y).at(location.x);
}

bool Field::inField(Location location) const {
    return 0 <= location.x && location.x < _size && 0 <= location.y && location.y < _size;
}

int Field::getSize() const {
    return _size;
}