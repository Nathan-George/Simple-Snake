#ifndef REPLAY_SNAKE_BEHAVIOR
#define REPLAY_SNAKE_BEHAVIOR

#include "core/SnakeBehavior.h"
#include <string>
#include <sstream>

class ReplaySnakeBehavior : public ISnakeBehavior {
public:
    ReplaySnakeBehavior(std::string moves_string);
    virtual ~ReplaySnakeBehavior();
    virtual Move getMove(const Snake& snake, const Field& field, const Apple& apple);
private:
    std::istringstream _stream;
};

#endif