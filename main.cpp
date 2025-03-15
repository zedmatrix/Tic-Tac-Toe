#include <iostream>
#include <string>
#include <format>
#include "Init.h"
#include "MainGame.hpp"

int main() {
    std::string welcome = std::format("Chapter {} - {}\n", 40, "AI for Tic-Tac-Toe");
    Init init(welcome);

    MainGame game;
    game.init();

    std::printf("%sPress Any Key to Continue!\n", init.cursorMove(22, 1).c_str());
    std::cout.flush();
    init.getch();
    return 0;
}


