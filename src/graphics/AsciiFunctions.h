#ifndef ASCII_FUNCTIONS_H
#define ASCII_FUNCTIONS_H

#include "AsciiCanvas.h"
#include "../core/SnakeGame.h"

void draw_snake(AsciiCanvas& canvas, const Snake& snake);
void draw_apple(AsciiCanvas& canvas, const Apple& apple);

#endif