#include "MainGame.hpp"


MainGame::MainGame() {

}
std::string MainGame::locateYX(int rowY, int colX) {
    return std::format("\033[{};{}H", rowY, colX);
}
void MainGame::clearScreen() {
    std::cout << "\033[2J\033[1H";
}
void MainGame::print(std::string text) {
    std::printf("%s%s", locateYX(_screenHeight - 2, 1).c_str(), std::string(_screenWidth, ' ').c_str());
    std::printf("%s%s", locateYX(_screenHeight - 2, _screenWidth / 2 - 3).c_str(), text.c_str());
    std::cout.flush();

}
void MainGame::screenSize() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    _screenWidth = w.ws_col;
    _screenHeight = w.ws_row;
}

char MainGame::getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void MainGame::init() {
    screenSize();
    int width = 4; //0-3
    int gridHeight = 3;
    int gridWidth = 3; // 3 wide
    int offsetX = (_screenWidth / 2) - ((width * gridWidth) / 2);

    _gameState = GameState::PLAYING;
    _currentPlayer = X_VAL;
    _board.init(4, offsetX, 4, width, gridHeight, gridWidth);

    playerName[NO_VAL] = "invalid";
    print("Multiplayer (y/n)?");
    _inkey = getch();
    if (_inkey == 'Y' || _inkey == 'y') {
        _isMultiPlayer = true;
    } else {
        _isMultiPlayer = false;
    }

    if (!_isMultiPlayer) {

        // Get player
        print("Would you like to be (X or O)?");
        _inkey = getch();
        if (_inkey == 'x' || _inkey == 'X') {
            _aiPlayer = O_VAL;
            playerName[O_VAL] = "AI O Turn";
            playerName[X_VAL] = "Human X Turn";
        } else if (_inkey == 'o' || _inkey == 'O') {
            _aiPlayer = X_VAL;
            playerName[X_VAL] = "AI X Turn";
            playerName[O_VAL] = "Human O Turn";
        }
        _ai.init(_aiPlayer);
    } else {
        playerName[X_VAL] = "Human X Turn";
        playerName[O_VAL] = "Human O Turn";
    }

    while (_gameState != GameState::EXIT) {
        _board.drawGrid();
        if (_currentPlayer == X_VAL) {
            print(" Player X's turn! ");
        } else {
            print(" Player O's turn! ");
        }
        // Perform a move
        if (!_isMultiPlayer && _currentPlayer == _aiPlayer) {
            aiMove();
        } else {
            playerMove();
        }
        // Check victory condition
        int rv = _board.checkVictory();
        if (rv != NO_VAL) {
            endGame(rv == TIE_VAL);
        } else {
            changePlayer();
        }

    }
}
void MainGame::playerMove() {
    // Get input
    bool wasValid = false;

    int x, y;
    do {
        _text = std::format("Player {} Enter the X:", playerName[_currentPlayer]);
        print(_text);
        x = getch() - 48;
        _text = std::format("Player {} Enter the O:", playerName[_currentPlayer]);
        print(_text);
        y = getch() - 48;

        if (x < 1 || y < 1 || x > _board.getSize() || y > _board.getSize()) {
            print(" ERROR: Invalid X or Y! ");
        } else if (_board.getVal(x - 1, y - 1) != 0) {
            print(" ERROR: That spot is taken! ");
        } else {
            wasValid = true;
        }

    } while (!wasValid);
    // Now place the token
    _board.setVal(x - 1, y - 1, _currentPlayer);
    _board.printGlyph(_currentPlayer, y - 1, x - 1);
}

void MainGame::aiMove() {
    _ai.performMove(_board);
}

void MainGame::changePlayer() {
    if (_currentPlayer == X_VAL) {
        _currentPlayer = O_VAL;
    } else {
        _currentPlayer = X_VAL;
    }
}

void MainGame::endGame(bool wasTie) {
    if (wasTie) {
        print(" Tie game! Enter any key to play again, or Q to quit: ");
    } else {
        _text = std::format("Player {} Wins! Any Key to Continue or Q to Quit", playerName[_currentPlayer]);
        print(_text);
    }

    _inkey = getch();
    if (_inkey == 'q' || _inkey == 'Q') {
        _gameState = GameState::EXIT;
    } else {
        clearScreen();
        init();
    }
}
