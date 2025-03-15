#include "Board.h"

const char GLYPHS[3][3][3] = {
    {
        { ' ', ' ', ' '},
        { ' ', ' ', ' '},
        { ' ', ' ', ' '}
    },
    {
        { '#', ' ', '#'},
        { ' ', '#', ' '},
        { '#', ' ', '#'}
    },
    {
        { '#', '#', '#'},
        { '#', ' ', '#'},
        { '#', '#', '#'},
    }
};

Board::Board() {

}

std::string Board::locateYX(int rowY, int colX) {
    return std::format("\033[{};{}H", rowY, colX);
}

void Board::init(int offsetY, int offsetX, int height, int width, int &gridHeight, int &gridWidth) {
    _offsetY = offsetY;
    _offsetX = offsetX;
    _height = height;
    _width = width;
    _gridHeight = gridHeight;
    _gridWidth = gridWidth;
    _size = gridHeight;
    // Set the board size
    _board.resize(_gridHeight * _gridWidth);
    clear();
    getBox(1, 1);
}
void Board::clear() {
    for (size_t i = 0; i < _board.size(); i++) {
        _board[i] = NO_VAL;
    }
}
void Board::print() {
    for (size_t i = 0; i < _board.size(); i++) {
        std::cout << locateYX(10 + i, _offsetX / 2) << _board[i];
    }
}

void Board::getBox(int rowY, int colX) {
    _startY = _offsetY + ((_height + 1) * rowY);
    _startX = _offsetX + ((_width + 1) * colX);
}

void Board::drawGrid() {
    int bottom = _offsetY + (_gridHeight * _height );
    for (int j = 0; j < _gridHeight; j++) {

        for (int i = 0; i < _gridWidth; i++) {
            getBox(j, i);
            if (i == 0) std::printf("%s%d", locateYX(_startY + _height / 2, _startX - 2).c_str(), j + 1);
            std::printf("%s%d", locateYX(bottom + 3, _startX + 2).c_str(), i + 1);
            drawBox();
        }
    }
}

void Board::drawBox() {
    std::cout << locateYX(_startY, _startX) << topLeft << locateYX(_startY, _startX + _width) << topRight;
    std::cout << locateYX(_startY + _height, _startX) << botLeft << locateYX(_startY + _height, _startX + _width) << botRight;
    for (int x = 1; x < _width; x++) {
        std::cout << locateYX(_startY, x + _startX) << horiz;
        std::cout << locateYX(_startY + _height, x + _startX) << horiz;
    }
    for (int y = 1; y < _height; y++) {
        std::cout << locateYX(y + _startY, _startX) << verti;
        std::cout << locateYX(y + _startY, _startX + _width) << verti;
    }

}
void Board::printGlyph(int index, int rowY, int colX) {
    if (index < 0 || index >= 3) {
        std::cerr << "Invalid glyph index: " << index << '\n';
        return;
    }
    getBox(rowY, colX);
    for (int i = 0; i < 3; ++i) {
        std::cout << std::format("{}{}{}{}",
            locateYX(_startY + 1 + i, _startX + 1),
            GLYPHS[index][i][0],
            GLYPHS[index][i][1],
            GLYPHS[index][i][2]
        );
    }
}
int Board::checkVictory() const {
    bool victory;
    int c;
    // Check the rows
    for (int y = 0; y < _size; y++) {
        c = getVal(0, y);
        if (c != NO_VAL) {
            victory = true;
            for (int x = 0; x < _size; x++) {
                if (getVal(x, y) != c) {
                    victory = false;
                    break;
                }
            }
            if (victory) return c;
        }
    }

    // Check the columns
    for (int x = 0; x < _size; x++) {
        c = getVal(x, 0);
        if (c != NO_VAL) {
            victory = true;
            for (int y = 0; y < _size; y++) {
                if (getVal(x, y) != c) {
                    victory = false;
                    break;
                }
            }
            if (victory) return c;
        }
    }

    // Check top left diagonal
    c = getVal(0, 0);
    if (c != NO_VAL) {
        victory = true;
        for (int xy = 0; xy < _size; xy++) {
            if (getVal(xy, xy) != c) {
                victory = false;
                break;
            }
        }
        if (victory) return c;
    }

    // Check top right diagonal
    c = getVal(_size - 1, 0);
    if (c != NO_VAL) {
        victory = true;
        for (int xy = 0; xy < _size; xy++) {
            if (getVal(_size - xy - 1, xy) != c) {
                victory = false;
                break;
            }
        }
        if (victory) return c;
    }

    // Check for tie game
    for (size_t i = 0; i < _board.size(); i++) {
        if (_board[i] == NO_VAL) return NO_VAL;
    }
    // If we get here, every spot was filled, so return tie
    return TIE_VAL;
}
