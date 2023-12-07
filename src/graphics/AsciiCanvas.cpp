
#include "AsciiCanvas.h"

#include <iostream>

AsciiCanvas::AsciiCanvas(const int width, const int height) : AsciiCanvas(width, height, 2) {}
AsciiCanvas::AsciiCanvas(const int width, const int height, const int blockWidth) : 
    _width(width), 
    _height(height), 
    _blockWidth(blockWidth), 
    _canvas(height, std::vector<std::string>(width, std::string(blockWidth, ' '))) {}

void AsciiCanvas::draw() const {
    std::cout << "┌"; for (int i = 0; i < _width*_blockWidth; i++) std::cout << "─"; std::cout << "─┐\n";
    for (int i = _height-1; i >= 0; i--) {
        std::cout << "│";
        for (int j = 0; j < _width; j++) {
            std::cout << _canvas[i][j];
        }
        std::cout << " │\n";
    }
    std::cout << "└"; for (int i = 0; i < _width*_blockWidth; i++) std::cout << "─"; std::cout << "─┘\n";
}

void AsciiCanvas::clear() {
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            _canvas[i][j] = std::string(_blockWidth, ' ');
        }
    }
}

std::string& AsciiCanvas::at(int x, int y) {
    return _canvas.at(y).at(x);
}

int AsciiCanvas::getWidth() const {
    return _width;
}

int AsciiCanvas::getHeight() const {
    return _height;
}