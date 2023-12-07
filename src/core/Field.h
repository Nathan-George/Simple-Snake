#ifndef FIELD_H
#define FIELD_H

#include "Location.h"

#include <vector>

class FieldCell {
public:
    /**
     * @brief Construct an empty Field Cell object
     * 
     */
    FieldCell();
    /**
     * @brief Construct a snake Field Cell object with an index
     * 
     * @param index the index of the snake node
     */
    FieldCell(int index);

    /**
     * @brief Checks if the field is empty at this location.
     * 
     * @return true if the cell is empty
     * @return false if the cell is part of the snake
     */
    bool isEmpty() const;
    /**
     * @brief Checks if the field is part of the snake.
     * 
     * @return true if the cell is part of the snake
     * @return false if the cell is empty
     */
    bool isSnakeNode() const;

    /**
     * @brief Updates the index data if the cell is part of the snake.
     * 
     * @param index the new index
     */
    void updateIndex(int index);

    /**
     * @brief Gets the index of the node if the cell is part of the snake.
     * 
     * @return int the index of the node (0 is the head)
     */
    int index() const;

    /**
     * @brief Gets the index of the node if the cell is part of the snake. If
     * the cell is empty, it will just return the value.
     * 
     * @param value the value
     * @return int the int the index of the node (0 is the head)
     */
    int indexOr(int value) const;

private:
    bool _isSnakeNode;
    int _snakeNodeIndex;
};

class Field {
public:
    Field(int size);

    /**
     * @brief constant Read Only access to the field cells
     * 
     * @param location the location to check
     * @return const FieldCell& the field cell at that location
     */
    const FieldCell& at(Location location) const;
    /**
     * @brief Read/Write access to the field cells
     * 
     * @param location the location to check
     * @return const FieldCell& the field cell at that location
     */
    FieldCell& at(Location location);

    /**
     * @brief Checks if a location is in the field
     * 
     * @param location the location
     * @return true if the location is in the field
     * @return false if the location is out of bounds
     */
    bool inField(Location location) const;

    /**
     * @brief Get the size of the field
     * 
     * @return int the size
     */
    int getSize() const;

private:
    std::vector<std::vector<FieldCell>> _field;

    int _size;
};

#endif