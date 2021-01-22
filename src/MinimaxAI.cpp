#include "../include/MinimaxAI.h"
#include <vector>

using namespace std;

#define DEPTH 5
#define INF 99999999

int maxValue(Game &game, char piece, int actualDepth, int depth);
int minValue(Game &game, char piece, int actualDepth, int depth);
int heuristic(Game &game, char piece);

int MinimaxAI::nextMove(Game &game, char piece) {
    int w = game.getWidth(), h = game.getHeight();
    vector<vector<char>> table(w);
    for (int i = 0; i < w; i++) {
        vector<char> v(h);
        for (int j = 0; j < h; j++)
           v[j] = game.at(i, j);
        table.push_back(v);
    }

    int value = maxValue(game, piece, 0, DEPTH);

    int column = 0;
    for (int i = 0; i < w; i++) {
        if (!game.isColumnFilled(i)) {
            Game *next = game.clone();
            if (value == heuristic(*next, piece)) {
                column = i;
                delete next;
                break;
            } else
                delete next;
        }
    }

    return column;
}



int maxValue(Game &game, char piece, int actualDepth, int depth) {
    if (actualDepth >= depth) {
        return heuristic(game, piece);
    }

    int result = game.isFinished();
    if (result == TABLE_FULL)
        return 0;

    if ((piece == PIECE_X) ? result == WIN_X : result == WIN_O) {
        return INF;
    }

    int best = -INF;

    for (int i = 0; i < game.getWidth(); i++) {
        if (!game.isColumnFilled(i)) {
            Game * next = game.clone();
            int v = minValue(game, piece, actualDepth + 1, depth);
            if (v > best)
                best = v;
            delete next;
        }
    }

    return best;
}



int minValue(Game &game, char piece, int actualDepth, int depth) {
    if (actualDepth >= depth) {
        return heuristic(game, piece);
    }

    int result = game.isFinished();
    if (result == TABLE_FULL)
        return 0;

    if ((piece == PIECE_X) ? result == WIN_X : result == WIN_O) {
        return INF;
    }

    int best = INF;

    for (int i = 0; i < game.getWidth(); i++) {
        if (!game.isColumnFilled(i)) {
            Game * next = game.clone();
            int v = maxValue(game, piece, actualDepth + 1, depth);
            if (v < best)
                best = v;
            delete next;
        }
    }

    return best;
}



int heuristic(Game &game, char piece) {

    return 1;
}
