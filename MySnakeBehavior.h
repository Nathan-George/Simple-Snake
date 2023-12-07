#ifndef MY_SNAKE_BEHAVIOR
#define MY_SNAKE_BEHAVIOR

#include "src/core/SnakeBehavior.h"

class MySnakeBehavior : public ISnakeBehavior {
public:
    virtual ~MySnakeBehavior();
    virtual Move getMove(const Snake& snake, const Field& field, const Apple& apple);
};

#endif