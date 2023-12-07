
#include "Apple.h"

Location Apple::_generateLocation(const Field& field, const Snake& snake, unsigned int rng) const {
    int remainingLocations = field.getSize() * field.getSize() - snake.length();

    int locationIndex = rng % remainingLocations;

    for (int i = 0; i < field.getSize(); i++) {
        for (int j = 0; j < field.getSize(); j++) {
            if (field.at(Location(i, j)).isEmpty()) {
                if (locationIndex == 0) {
                    return Location(i, j);
                }
                locationIndex--;
            }
        }
    }
    return Location();
}

Apple::Apple(const Field& field, const Snake& snake, unsigned int rng) : _location(_generateLocation(field, snake, rng)) {}

Location Apple::getLocation() const {
    return _location;
}