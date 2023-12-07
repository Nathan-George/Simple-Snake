
#include "ExampleSnakeBehavior.h"

#include <array>
#include <deque>
#include <map>

#include <stdlib.h>

bool operator<(const Location& lhs, const Location& rhs) {
    if (lhs.x < rhs.x) return true;
    if (rhs.x < lhs.x) return false;
    return (lhs.y < rhs.y);
}

ExampleSnakeBehavior::~ExampleSnakeBehavior() {}

Move ExampleSnakeBehavior::getMove(const Snake& snake, const Field& field, const Apple& apple) {
    // search for shortest path
    std::deque<Location> search;
    std::map<Location, int> reached;

    search.push_back(snake.getHead());

    int i = 0;
    while (! search.empty() ) {
        Location location = search.front();
        search.pop_front();

        if (location == apple.getLocation()) {

            std::deque<Location> path;
            path.push_back(location);
            
            // find path
            while (path.front() != snake.getHead()) {
                int min = __INT_MAX__;
                Location start = path.front();
                path.push_front(Location());
                for (Location nextLocation : std::array<Location, 4>{{
                    {start.x+1, start.y}, 
                    {start.x-1, start.y},
                    {start.x, start.y+1},
                    {start.x, start.y-1}}}) {
                    
                    if (reached.count(nextLocation)==1 && reached.at(nextLocation) < min) {
                        min = reached.at(nextLocation);
                        path.pop_front();
                        path.push_front(nextLocation);
                    }
                }
            }

            // calculate move
            if (path.size() < 2) {
                return Move::Right;
            }

            if (path.at(1).x == path.at(0).x+1) return Move::Right;
            if (path.at(1).x == path.at(0).x-1) return Move::Left;
            if (path.at(1).y == path.at(0).y+1) return Move::Up;
            if (path.at(1).y == path.at(0).y-1) return Move::Down;
        }

        if (reached.count(location) == 1) continue;
        reached.insert({location, i++});

        

        for (Location nextLocation : std::array<Location, 4>{{
            {location.x+1, location.y}, 
            {location.x-1, location.y},
            {location.x, location.y+1},
            {location.x, location.y-1},}}) {

            if (! field.inField(nextLocation)) continue;
            if (field.at(nextLocation).isSnakeNode()) continue;

            search.push_back(nextLocation);
        }
    }

    // can't reach the apple!!
    return Move::Right;
}