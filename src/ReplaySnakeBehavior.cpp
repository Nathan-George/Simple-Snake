
#include "ReplaySnakeBehavior.h"

#include <stdexcept>

ReplaySnakeBehavior::ReplaySnakeBehavior(std::string moves_string) {
    _stream = std::istringstream(moves_string);
}

ReplaySnakeBehavior::~ReplaySnakeBehavior() {}

Move ReplaySnakeBehavior::getMove(const Snake& snake, const Field& field, const Apple& apple) {
    (void)snake;
    (void)field;
    (void)apple;

    switch (_stream.get())
    {
    case 'r':
        return Move::Right;
    case 'u':
        return Move::Up;
    case 'l':
        return Move::Left;
    case 'd':
        return Move::Down;
    
    default:
        break;
    }

    // unreachable
    throw std::invalid_argument("Not a valid move string");
}