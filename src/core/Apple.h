#ifndef APPLE_H
#define APPLE_H

#include "Field.h"
#include "Snake.h"

class Snake;
class Apple {
public:
    Apple(const Field& field, const Snake& snake, unsigned int rng);

    Location getLocation() const;

private:
    Location _generateLocation(const Field& field, const Snake& snake, unsigned int rng) const;
private:
    const Location _location;
};

#endif