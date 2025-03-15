#ifndef INIT_H
#define INIT_H

#include <iostream>
#include <string>
#include <format>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

class Init {

public:
    Init(std::string welcome) {
        int stars = welcome.size();
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int xpos = (w.ws_col / 2) - (stars / 2);
        std::cout << clearScreen();
        std::cout << cursorMove(1, xpos) << outStars(stars);
        std::cout << cursorMove(2, xpos) << _white << welcome << _normal;
        std::cout << cursorMove(3, xpos) << outStars(stars);
    }
    std::string outStars(int numStars) const { return std::format("{}{}{}\n",_green, std::string(numStars, '*'), _normal); };
    std::string outChar(int x, char c) const { return std::format("{}{}{}",_red, std::string(x, c), _normal); };
    std::string cursorMove(int row, int col) const { return std::format("\033[{};{}H", row, col); } //move screen Y, X
    std::string clearScreen() const { return "\033[2J\033[H"; }
    std::string reset() const { return _normal; }
    char getch() {
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

private:
    std::string _red = "\033[1;31m";
    std::string _green = "\033[1;32m";
    std::string _yellow = "\033[1;33m";
    std::string _blue = "\033[1;34m";
    std::string _magenta = "\033[1;35m";
    std::string _cyan = "\033[1;36m";
    std::string _white = "\033[1;37m";
    std::string _normal = "\033[0m";
};

#endif //INIT_H
