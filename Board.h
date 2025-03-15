#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <format>
#include <vector>

const int TIE_VAL = -1;
// Indexes for board values
const int NO_VAL = 0;
const int X_VAL = 1;
const int O_VAL = 2;

class Board {

public:
    Board();

    void init(int offsetY, int offsetX, int height, int width, int &gridHeight, int &gridWidth);
    void drawBox();
    void drawGrid();
    void printGlyph(int index, int rowY, int colX);
    void print();

    int checkVictory() const;
    // Sets value at x,y spot
    void setVal(int x, int y, int val) {
        _board[y * _size + x] = val;
    }
    // Gets value at x,y spot
    int getVal(int x, int y) const {
        return _board[y * _size + x];
    }
    // Getters
    int getSize() const { return _size; }

private:
    void clear();
    void getBox(int rowY, int colX);
    std::string locateYX(int rowY, int colX);
    const std::string topLeft = "\u2554";
    const std::string topRight = "\u2557";
    const std::string botLeft = "\u255A";
    const std::string botRight = "\u255D";
    const std::string verti = "\u2551";
    const std::string horiz = "\u2550";
    int _offsetY;
    int _offsetX;
    int _startY;
    int _startX;
    int _height;
    int _width;
    int _gridHeight;
    int _gridWidth;
    int _size;
    std::vector<int> _board;

};

#endif //BOARD_H
