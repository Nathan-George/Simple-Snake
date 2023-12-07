#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "SnakeBehavior.h"

#include "RandomGenerator.h"

#include "Field.h"
#include "Apple.h"
#include "Snake.h"

class SnakeGame {
public:
    SnakeGame(ISnakeBehavior* snakeBehavior);
    SnakeGame(ISnakeBehavior* snakeBehavior, int size);
    SnakeGame(ISnakeBehavior* snakeBehavior, int size, unsigned int seed);

    SnakeGame(const SnakeGame& other) = delete;

    ~SnakeGame();

    SnakeGame& operator=(const SnakeGame other) = delete;

    void step();
    bool isFinished() const;

    const Field& getField() const;
    const Apple& getApple() const;
    const Snake& getSnake() const;

    Move getLastMove() const;
private:
    RandomGenerator _rand;

    Field* _pField;
    Apple* _pApple;
    Snake* _pSnake;

    Move _lastMove;
};

#endif