#include "../include/MinimaxAI.h"
#include <vector>
#include <iostream>


using namespace std;

#define DEPTH 2
#define INF 99999999
#define column first
#define value second

pair<int, int> maxValue(Game &game, char piece, int actualDepth, int depth);
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

    pair<int, int> sol = maxValue(game, piece, 0, DEPTH);
    cout << "heuristic obtained: " << sol.value << endl;
    return sol.column;
}



pair<int, int> maxValue(Game &game, char piece, int actualDepth, int depth) {
    if (actualDepth >= depth) {
        return {0,heuristic(game, piece)};
    }

    int result = game.isFinished();
    if (result == TABLE_FULL)
        return {0,0};

    if (result == WIN_X) {
        return {0, INF};
    } else if (result == WIN_O){
        return {0, -INF};
    }

    int best = -INF;
    int decision = 0;

    for (int i = 0; i < game.getWidth(); i++) {
        if (!game.isColumnFilled(i)) {
            Game * next = game.clone();
            next->insertPiece(piece, i);
            int v = minValue(*next, piece, actualDepth + 1, depth);
            if (v > best){
                best = v;
                decision = i;
            }
            delete next;
        }
    }

    return {decision, best};
}



int minValue(Game &game, char piece, int actualDepth, int depth) {
    if (actualDepth >= depth) {
        return heuristic(game, piece);
    }

    int result = game.isFinished();
    if (result == TABLE_FULL)
        return 0;

    if (result == WIN_X) {
        return INF;
    } else if (result == WIN_O){
        return -INF;
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
    bool visited[game.getWidth()][game.getHeight()];
    for(int i = 0; i<game.getWidth(); i++)
        for(int j = 0; j<game.getHeight(); j++)
            visited[i][j] = false;
    for(int i = 0; i < game.getWidth(); i++)
        for(int j = game.getHeight(); j >= 0 && !visited[i][j] && game.at(i,j) != EMPTY; j--){
            char actual = game.at(i, j);
            // count horizontal consecutives
            int cont = 1;
            int J = j - 1;
            while (J >= 0 && game.at(i,J) == actual) {
                cont++;
                J--;
                visited[i][J] = true;
            }
            J = j + 1;
            while (J < game.getWidth() && game.at(i, J) == actual) {
                cont++;
                J++;
                visited[i][J] = true;
            }
            longitudes[2*(actual==piece)+cont]++;

            // count vertical consecutives
            cont = 1;
            int I = i-1;
            while (I >= 0 && game.at(I,j) == actual) {
                cont++;
                I--;
                visited[I][j] = true;
            }
            I = i + 1;
            while (I < game.getHeight() && game.at(I, j) == actual) {
                cont++;
                I++;
                visited[I][j] = true;
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
                visited[I][J] = true;
            }
            I = i + 1;
            J = j + 1;
            while (I < game.getWidth() && J < game.getHeight() && game.at(I, J) == actual) {
                cont++;
                I++;
                J++;
                visited[I][J] = true;
            }
            longitudes[2*(actual==piece)+cont]++;

            // count diagonal DOWN->UP consecutives
            cont = 1;
            I = i + 1;
            J = j - 1;
            while (I < game.getWidth() && J >= 0 && game.at(I,J) == actual) {
                cont++;
                I++;
                J--;
                visited[I][J] = true;
            }
            I = i - 1;
            J = j + 1;
            while (I >= 0 && J < game.getWidth() && game.at(I, J) == actual) {
                cont++;
                I--;
                J++;
                visited[I][J] = true;
            }
            longitudes[3*(actual==piece)+cont]++;
            
        }
    int results = longitudes[4]-longitudes[1] + longitudes[5]-longitudes[2] + longitudes[6]-longitudes[3];
    //cout << results << endl;
    return results;
}
