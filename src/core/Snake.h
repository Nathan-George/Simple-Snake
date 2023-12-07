#ifndef SNAKE_H
#define SNAKE_H

#include "SnakeBehavior.h"

#include "Location.h"
#include "Apple.h"
#include "Field.h"

#include <deque>
#include <vector>


enum class Move {
    Right,
    Up,
    Left,
    Down,
};

class Apple;
class ISnakeBehavior;
class Snake {
public:
    /**
     * @brief Construct a new Snake object with the head at index 0
     * 
     * @param pBehavior a pointer to a snake behavior
     * @param field a reference to the field for the snake to update with its locations
     */
    Snake(ISnakeBehavior* const pBehavior, Field& field);
    /**
     * @brief Construct a new Snake object
     * 
     * @param pBehavior a pointer to a snake behavior
     * @param field a reference to the field for the snake to update with its locations
     * @param headNode the location of the head of the Snake
     */
    Snake(ISnakeBehavior* const pBehavior, Field& field, const Location headNode);
    /**
     * @brief Construct a new Snake object
     * 
     * @param pBehavior a pointer to a snake behavior
     * @param field a reference to the field for the snake to update with its locations
     * @param nodes the location of the nodes for the snake (the head should be at index 0)
     */
    Snake(ISnakeBehavior* const pBehavior, Field& field, const std::vector<Location> &nodes);

    /**
     * @brief moves the snake and updates the field
     * 
     * @param field the field the snake is playing on
     * @param apple the location of the apple
     * @return Move the move that the snake just played
     */
    Move move(Field& field, const Apple& apple);

    /**
     * @brief Gets the location of a snake node 
     * 
     * @param index the index of the snake node (0 is the head)
     * @return Location the location of the snake node
     */
    Location getLocationAt(int index) const;

    /**
     * @brief Get the length of the snake
     * 
     * @return unsigned int the length of the snake
     */
    unsigned int length() const;
    /**
     * @brief Get the location of the snake's head
     * 
     * @return Location the location of the snake's head
     */
    Location getHead() const;
    /**
     * @brief Get the location of the snake's tail
     * 
     * @return Location the location of the snake's tail
     */
    Location getTail() const;

private:
    ISnakeBehavior* const _pBehavior;
    std::deque<Location> _nodes;
};

#endif