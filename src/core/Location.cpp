
#include "Location.h"

Location::Location() : Location(0, 0) {}
Location::Location(const int x, const int y) : x(x), y(y) {}

bool Location::operator==(const Location other) {
    return x == other.x && y == other.y;
}

bool Location::operator!=(const Location other) {
    return x != other.x || y != other.y;
}