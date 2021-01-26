#include "../include/MinimaxAI.h"
#include <vector>
#include <iostream>

//#define DEBUG

using namespace std;

#define DEPTH 9
#define INF 99999999
#define column first
#define value second

pair<int, int> maxValue(Game &game, int n, char piece, int actualDepth, int depth, int alpha, int beta);
int minValue(Game &game, int n, char piece, int actualDepth, int depth, int alpha, int beta);
int heuristic(Game &game, char piece);

int MinimaxAI::nextMove(Game &game, char piece) {

    pair<int, int> sol;
    for (int i = 0; i < game.getWidth(); i++) {
        if (!game.isColumnFilled(i)) {
            sol = maxValue(*game.clone(), i, piece, 0, DEPTH, -INF, INF);
            break;
        }
    }

    cout << "heuristic obtained: " << sol.value << endl << "column decided: " << sol.column + 1 << endl;
    return sol.column;
}



pair<int, int> maxValue(Game &game, int n, char piece, int actualDepth, int depth, int alpha, int beta) {
    int result = game.getGameStatus();
    if (result == TABLE_FULL)
        return {n,0};

    if (piece == PIECE_PLAYER_1) {
        if (result == WIN_PLAYER_1)
            return {n, INF};
        else if (result == WIN_PLAYER_2) {
            return {n, -INF};
        }
    }
    else if (piece == PIECE_PLAYER_2) {
        if (result == WIN_PLAYER_1)
            return {n, -INF};
        else if (result == WIN_PLAYER_2)
            return {n, INF};
    }

    if (actualDepth >= depth) {
        return {n, heuristic(game, piece)};
    }

    int best = -INF;
    int decision = n;

#ifdef DEBUG
    cout << "Decisiones a tomar: ";
#endif
    for (int i = 0; i < game.getWidth(); i++) {
        if (!game.isColumnFilled(i)) {
            Game * next = game.clone();
            next->insertPiece(piece, i);
            int v = minValue(*next, i, piece == PIECE_PLAYER_1 ? PIECE_PLAYER_2 : PIECE_PLAYER_1, actualDepth + 1, depth, alpha, beta);
#ifdef DEBUG
            cout << v << " ";
#endif
            delete next;
            if (v > best){
                best = v;
                decision = i;
            }
            if (best >= beta) {
                return {decision, best};
            }
            alpha = max(best, alpha);
        }
    }
#ifdef DEBUG
    cout << endl;
#endif
    return {decision, best};
}



int minValue(Game &game, int n, char piece, int actualDepth, int depth, int alpha, int beta) {
    int result = game.getGameStatus();
    if (result == TABLE_FULL)
        return 0;

    if (piece == PIECE_PLAYER_1) {
        if (result == WIN_PLAYER_1)
            return -INF;
        else if (result == WIN_PLAYER_2)
            return INF;
    }
    else if (piece == PIECE_PLAYER_2) {
        if (result == WIN_PLAYER_1)
            return INF;
        else if (result == WIN_PLAYER_2)
            return -INF;
    }

    if (actualDepth >= depth) {
        return heuristic(game, piece);
    }

    int best = INF;

    for (int i = 0; i < game.getWidth(); i++) {
        if (!game.isColumnFilled(i)) {
            Game * next = game.clone();
            next->insertPiece(piece, i);
            int v = maxValue(*next, i, piece == PIECE_PLAYER_1 ? PIECE_PLAYER_2 : PIECE_PLAYER_1, actualDepth + 1, depth, alpha, beta).value;
            delete next;
            if (v < best)
                best = v;
            if (best <= alpha)
                return best;
            beta = min(best, beta);

        }
    }

    return best;
}



int heuristic(Game &game, char piece) { // Es una mierda
    int longitudes[10];
    for(int i = 0; i<10; i++)
        longitudes[i] = 0;

    for(int i = 0; i < game.getHeight(); i++)
        for(int j = game.getWidth(); j >= 0 && game.at(i,j) != EMPTY; j--){
            char actual = game.at(i, j);
            // count horizontal consecutives
            int cont = 1;
            int J = j - 1;
            while (J >= 0 && game.at(i,J) == actual) {
                cont++;
                J--;
            }
            J = j + 1;
            while (J < game.getWidth() && game.at(i, J) == actual) {
                cont++;
                J++;
            }
            longitudes[2*(actual==piece)+cont]++;

            // count vertical consecutives
            cont = 1;
            int I = i-1;
            while (I >= 0 && game.at(I,j) == actual) {
                cont++;
                I--;
            }
            I = i + 1;
            while (I < game.getHeight() && game.at(I, j) == actual) {
                cont++;
                I++;
            }
            longitudes[2*(actual==piece)+cont]++;

            // count diagonal UP->DOWN consecutives
            cont = 1;
            I = i-1;
            J = j - 1;
            while (I >= 0 && J >= 0 && game.at(I,J) == actual) {
                cont++;
                I--;
                J--;
            }
            I = i + 1;
            J = j + 1;
            while (I < game.getHeight() && J < game.getWidth() && game.at(I, J) == actual) {
                cont++;
                I++;
                J++;
            }
            longitudes[2*(actual==piece)+cont]++;

            // count diagonal DOWN->UP consecutives
            cont = 1;
            I = i + 1;
            J = j - 1;
            while (I < game.getHeight() && J >= 0 && game.at(I,J) == actual) {
                cont++;
                I++;
                J--;
            }
            I = i - 1;
            J = j + 1;
            while (I >= 0 && J < game.getWidth() && game.at(I, J) == actual) {
                cont++;
                I--;
                J++;
            }
            longitudes[3*(actual==piece)+cont]++;
            
        }
    int results = longitudes[4]-longitudes[1] + longitudes[5]-longitudes[2] + longitudes[6]-longitudes[3];
    //cout << results << endl;
    return results;
}
