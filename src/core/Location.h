#ifndef LOCATION_H
#define LOCATION_H

struct Location {
    const int x;
    const int y;

    /**
     * @brief Construct a new Location object at (0, 0)
     * 
     */
    Location();
    /**
     * @brief Construct a new Location object
     * 
     * @param x the x Coordinate
     * @param y the y Coordinate
     */
    Location(const int x, const int y);

    bool operator==(const Location other);
    bool operator!=(const Location other);
};

#endif
