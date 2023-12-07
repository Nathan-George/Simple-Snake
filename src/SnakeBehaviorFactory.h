#ifndef SNAKE_BEHAVIOR_FACTORY_H
#define SNAKE_BEHAVIOR_FACTORY_H

#include "core/SnakeBehavior.h"

class SnakeBehaviorFactory {
public:
    ISnakeBehavior* constructSnakeBehavior() const;
};

#endif