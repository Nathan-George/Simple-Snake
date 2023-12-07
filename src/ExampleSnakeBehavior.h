#ifndef EXAMPLE_SNAKE_BEHAVIOR
#define EXAMPLE_SNAKE_BEHAVIOR

#include "core/SnakeBehavior.h"

class ExampleSnakeBehavior : public ISnakeBehavior {
public:
    virtual ~ExampleSnakeBehavior();
    virtual Move getMove(const Snake& snake, const Field& field, const Apple& apple);
private:
    
};

#endif