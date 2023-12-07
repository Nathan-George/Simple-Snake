
#include "SimpleSnakeBehavior.h"

SimpleSnakeBehavior::~SimpleSnakeBehavior() {}

Move SimpleSnakeBehavior::getMove(const Snake &snake, const Field &field, const Apple &apple) {
    apple.getLocation();

    Location headLocation = snake.getHead();

    if (headLocation == Location(0, 0)) {
        return Move::Right;
    }

    if (headLocation == Location(1, field.getSize() - 1)) {
        return Move::Left;
    }

    if (headLocation.x == 0) {
        return Move::Down;
    }

    if (headLocation.x == 1 && headLocation.y % 2 == 1) {
        return Move::Up;
    }

    if (headLocation.x == field.getSize() - 1 && headLocation.y % 2 == 0) {
        return Move::Up;
    }

    if (headLocation.y % 2 == 0) {
        return Move::Right;
    } else {
        return Move::Left;
    }
}