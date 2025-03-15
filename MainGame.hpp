#ifndef MAINGAME_HPP
#define MAINGAME_HPP
#include <iostream>
#include <string>
#include <array>
#include <format>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "Board.h"
#include "ai.hpp"

enum class GameState { PLAYING, EXIT };

class MainGame {

public:
    MainGame();
    void init();

private:
    AI _ai; // The AI player
    Board _board;
    GameState _gameState; // The state of the game

    void print(std::string text);
    void aiMove();
    void changePlayer();
    void playerMove();
    void endGame(bool wasTie);
    void screenSize();
    void clearScreen();
    std::string locateYX(int rowY, int colX);
    char getch();
    char _inkey;
    bool _isMultiPlayer;

    int _currentPlayer; // The index of the current player
    int _aiPlayer;      // Index of the AI player
    int _screenWidth;
    int _screenHeight;
    std::string _text;
    std::array <std::string, 3> playerName;

};

#endif //MAINGAME_HPP
