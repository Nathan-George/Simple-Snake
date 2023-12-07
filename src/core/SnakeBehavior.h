#ifndef SNAKE_BEHAVIOR_H
#define SNAKE_BEHAVIOR_H

#include "Snake.h"
#include "Field.h"
#include "Apple.h"

class Apple;
class Snake;
enum class Move;
class ISnakeBehavior {
public:
    virtual ~ISnakeBehavior(){}
    virtual Move getMove(const Snake& snake, const Field& field, const Apple& apple)=0;
};

#endif