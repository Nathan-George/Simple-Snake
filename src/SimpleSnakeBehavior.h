#ifndef SIMPLE_SNAKE_BEHAVIOR
#define SIMPLE_SNAKE_BEHAVIOR

#include "core/SnakeBehavior.h"

class SimpleSnakeBehavior : public ISnakeBehavior {
public:
    virtual ~SimpleSnakeBehavior();
    virtual Move getMove(const Snake& snake, const Field& field, const Apple& apple);
};

#endif