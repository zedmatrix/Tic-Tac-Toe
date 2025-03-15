#include "ai.hpp"

#include <vector>

void AI::init(int aiPlayer) {
    _aiPlayer = aiPlayer;
    _humanPlayer = _aiPlayer == X_VAL ? O_VAL : X_VAL;
}

void AI::performMove(Board& board) {
    AiMove bestMove = getBestMove(board, _aiPlayer);
    board.setVal(bestMove.x, bestMove.y, _aiPlayer);
    board.printGlyph(_aiPlayer, bestMove.y, bestMove.x);
}

AiMove AI::getBestMove(Board& board, int player, int depth /* = 0*/) {
    int retv = board.checkVictory();

    // if AI won, return great
    if (retv == _aiPlayer) {
        return AiMove(10 - depth);

    // if human won, return low
    } else if (retv == _humanPlayer) {
        return AiMove(depth - 10);

    // if nobody won, return 0
    } else if (retv == TIE_VAL) {
        return AiMove(0);
    }

    // make sure you make it the always hardest for the human
    depth++;
    std::vector<AiMove> moves;

    // loop through holes
    for (int y = 0; y < board.getSize(); y++) {

        for (int x = 0; x < board.getSize(); x++) {

            if (board.getVal(x, y) == NO_VAL) {

                AiMove move;
                move.x = x;
                move.y = y;

                board.setVal(x, y, player);

                // check if a good move
                move.score = getBestMove(board, player == _aiPlayer ? _humanPlayer : _aiPlayer, depth).score;

                moves.push_back(move);

                board.setVal(x, y, NO_VAL);
            }
        }
    }

    // pick the best move
    int bestMove = 0;
    if (player == _aiPlayer) {

        int bestScore = -1000;
        for (size_t i = 0; i < moves.size(); i++) {

            if (moves[i].score > bestScore) {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    } else {
        int bestScore = 1000;
        for (size_t i = 0; i < moves.size(); i++) {
            if (moves[i].score < bestScore) {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }
    return moves[bestMove];
}
