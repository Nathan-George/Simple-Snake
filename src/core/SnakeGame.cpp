
#include "SnakeGame.h"

SnakeGame::SnakeGame(ISnakeBehavior* snakeBehavior) : SnakeGame(snakeBehavior, 30) {}
SnakeGame::SnakeGame(ISnakeBehavior* snakeBehavior, int size) : SnakeGame(snakeBehavior, size, 0) {}
SnakeGame::SnakeGame(ISnakeBehavior* snakeBehavior, int size, unsigned int seed) {
    _rand = RandomGenerator(seed);
    _rand.get();

    _pField = new Field(size);
    _pSnake = new Snake(snakeBehavior, *_pField, Location(0, 0));
    _pApple = new Apple(*_pField, *_pSnake, _rand.get());
}

SnakeGame::~SnakeGame() {
    delete _pField;
    delete _pSnake;
    delete _pApple;
}

void SnakeGame::step() {
    _lastMove = _pSnake->move(*_pField, *_pApple);

    // check if the snake ate the apple
    if (!isFinished() && _pSnake->getHead() == _pApple->getLocation()) {
        delete _pApple;
        _pApple = new Apple(*_pField, *_pSnake, _rand.get());
    }
}

bool SnakeGame::isFinished() const {
    return static_cast<int>(_pSnake->length()) == _pField->getSize() * _pField->getSize();
}

const Field& SnakeGame::getField() const {
    return *_pField;
}

const Apple& SnakeGame::getApple() const {
    return *_pApple;
}

const Snake& SnakeGame::getSnake() const {
    return *_pSnake;
}

Move SnakeGame::getLastMove() const {
    return _lastMove;
}