#include "../include/MinimaxAI.h"
#include <vector>
#include <iostream>

//#define DEBUG

using namespace std;

#define DEPTH 6
#define INF 99999999
#define column first
#define value second

pair<int, int> maxValue(Game &game, char piece, int actualDepth, int depth);
int minValue(Game &game, char piece, int actualDepth, int depth);
int heuristic(Game &game, char piece);

int MinimaxAI::nextMove(Game &game, char piece) {

    pair<int, int> sol = maxValue(*game.clone(), piece, 0, DEPTH);
    cout << "heuristic obtained: " << sol.value << endl << "column decided: " << sol.column + 1 << endl;
    return sol.column;
}



pair<int, int> maxValue(Game &game, char piece, int actualDepth, int depth) {
    int result = game.isFinished();
    if (result == TABLE_FULL)
        return {0,0};

    if (result == WIN_X) {
        return {0, -INF};
    } else if (result == WIN_O){
        return {0, INF};
    }

    if (actualDepth >= depth) {
        return {0,heuristic(game, piece)};
    }

    int best = -INF;
    int decision = 0;

#ifdef DEBUG
    cout << "Decisiones a tomar: ";
#endif
    for (int i = 0; i < game.getWidth(); i++) {
        if (!game.isColumnFilled(i)) {
            Game * next = game.clone();
            next->insertPiece(piece, i);
            int v = minValue(*next, piece, actualDepth + 1, depth);
#ifdef DEBUG
            cout << v << " ";
#endif
            if (v > best){
                best = v;
                decision = i;
            }
            delete next;
        }
    }
#ifdef DEBUG
    cout << endl;
#endif
    return {decision, best};
}



int minValue(Game &game, char piece, int actualDepth, int depth) {
    int result = game.isFinished();
    if (result == TABLE_FULL)
        return 0;

    if (result == WIN_X) {
        return -INF;
    } else if (result == WIN_O){
        return INF;
    }

    if (actualDepth >= depth) {
        return heuristic(game, piece);
    }

    int best = INF;

    for (int i = 0; i < game.getWidth(); i++) {
        if (!game.isColumnFilled(i)) {
            Game * next = game.clone();
            next->insertPiece(PIECE_X, i);
            int v = maxValue(*next, piece, actualDepth + 1, depth).value;
            if (v < best)
                best = v;
            delete next;
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
