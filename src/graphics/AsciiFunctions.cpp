
#include "AsciiFunctions.h"

void draw_snake(AsciiCanvas& canvas, const Snake& snake) {

    enum Shape {
        RIGHT = 1u << 0,
        UP = 1u << 1,
        LEFT = 1u << 2,
        DOWN = 1u << 3,
    };

    std::vector<std::vector<unsigned int>> directionField(canvas.getHeight(), std::vector<unsigned int>(canvas.getWidth(), 0));
    for (unsigned int i = 1; i < snake.length(); i++) {
        int dx = snake.getLocationAt(i).x - snake.getLocationAt(i-1).x;
        int dy = snake.getLocationAt(i).y - snake.getLocationAt(i-1).y;

        unsigned int& prev = directionField.at(snake.getLocationAt(i-1).y).at(snake.getLocationAt(i-1).x);
        unsigned int& next = directionField.at(snake.getLocationAt(i).y).at(snake.getLocationAt(i).x);

        if (dx == 1) {
            prev |= RIGHT;
            next |= LEFT;
        } else if (dx == -1) {
            prev |= LEFT;
            next |= RIGHT;
        } else if (dy == 1) {
            prev |= UP;
            next |= DOWN;
        } else if (dy == -1) {
            prev |= DOWN;
            next |= UP;
        }
    }

    for (int i = 0; i < canvas.getHeight(); i++) {
        for (int j = 0; j < canvas.getHeight(); j++) {
            switch(directionField.at(i).at(j)) {
            case (DOWN | UP):
                canvas.at(j, i) = " ║";
                break;
            case (LEFT | RIGHT):
                canvas.at(j, i) = "══";
                break;
            case (RIGHT | UP):
                canvas.at(j, i) = " ╚";
                break;
            case (UP | LEFT):
                canvas.at(j, i) = "═╝";
                break;
            case (LEFT | DOWN):
                canvas.at(j, i) = "═╗";
                break;
            case (DOWN | RIGHT):
                canvas.at(j, i) = " ╔";
                break;
            }
        }
    }
    
    unsigned int tailShape = directionField.at(snake.getTail().y).at(snake.getTail().x);
    canvas.at(snake.getTail().x, snake.getTail().y) = 
        tailShape == RIGHT ? " <" :
        tailShape == UP ?    " v" :
        tailShape == LEFT ?  "═>" :
        tailShape == DOWN ?  " ^" :
        "  ";
    
    unsigned int headShape = directionField.at(snake.getHead().y).at(snake.getHead().x);
    canvas.at(snake.getHead().x, snake.getHead().y) = 
        headShape == RIGHT ? " o" :
        headShape == UP ?    " o" :
        headShape == LEFT ?  "═o" :
        headShape == DOWN ?  " o" :
        " o";
}

void draw_apple(AsciiCanvas& canvas, const Apple& apple) {
    canvas.at(apple.getLocation().x, apple.getLocation().y) = "🍎";
}