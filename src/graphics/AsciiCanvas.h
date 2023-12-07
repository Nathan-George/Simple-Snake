#ifndef ASCII_CANVAS_H
#define ASCII_CANVAS_H

#include <string>
#include <vector>

class AsciiCanvas {
public:
    AsciiCanvas(const int width, const int height);
    AsciiCanvas(const int width, const int height, const int blockWidth);

    void draw() const;
    void clear();

    std::string& at(int x, int y);

    int getWidth() const;
    int getHeight() const;

private:
    int _width;
    int _height;
    int _blockWidth;

    std::vector<std::vector<std::string>> _canvas;
};

#endif