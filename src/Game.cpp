#include <iostream>
#include "../include/Game.h"
using namespace std;

Game::Game(int _n, int _w, int _h) {
    n = _n;
    w = _w;
    h = _h;
    
    // TODO make this table all togheter

    table = new char*[h];
    for (int i = 0; i < h; i++)
        table[i] = new char[w];

    piecePosition = new int[w];
}

Game::~Game() {
    for (int i = 0; i < h; i++)
        delete[] table[i];
    delete[] table;

    delete[] piecePosition;
}

Game* Game::clone() {
    Game* newGame = new Game(n, w, h);

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            newGame->table[i][j] = table[i][j];

    for(int i = 0; i < w; i++)
        newGame->piecePosition[i] = piecePosition[i];

    return newGame;
}

int Game::getWidth() const {
    return w;
}

int Game::getHeight() const {
    return h;
}

char Game::at(int i, int j) const {
    return table[i][j];
};

void Game::init() {
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            table[i][j] = EMPTY;

    for(int i = 0; i < w; i++)
        piecePosition[i] = h - 1;
}

bool Game::insertPiece(char piece, int column) {
    if (piecePosition[column] < 0)
        return false;

    table[piecePosition[column]][column] = piece;
    piecePosition[column]--;
    return true;
}

int Game::isFinished() {
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (table[i][j] != EMPTY && (checkHorizontal(i, j) || checkVertical(i, j) || checkDiagonalUpToDown(i, j) || checkDiagonalDownToUp(i, j)))
                return table[i][j] == PIECE_X ? WIN_X : WIN_O;

    for (int i = 0; i < w; i++)
        if (piecePosition[i] >= 0)
            return UNFINISHED;
    return TABLE_FULL;
}

bool Game::checkHorizontal(int i, int j) {
    char actual = table[i][j];
    int cont = 1;

    int J = j + 1;
    while (J < w && table[i][J] == actual) {
        cont++;
        if (cont >= n)
            return true;
        J++;
    }

    return false;
}

bool Game::checkVertical(int i, int j) {
    char actual = table[i][j];
    int cont = 1;

    int I = i + 1;
    while (I < h && table[I][j] == actual) {
        cont++;
        if (cont >= n)
            return true;
        I++;
    }

    return false;
}

bool Game::checkDiagonalUpToDown(int i, int j) {
    char actual = table[i][j];
    int cont = 1;
    int I = i + 1, J = j + 1;
    while (I < h && J < w && table[I][J] == actual) {
        cont++;
        if (cont >= n)
            return true;
        I++;
        J++;
    }

    return false;
}

bool Game::checkDiagonalDownToUp(int i, int j) {
    char actual = table[i][j];
    int cont = 1;

    int I = i + 1, J = j - 1;
    while (I < h && J >= 0 && table[I][J] == actual) {
        cont++;
        I++;
        J--;
    }

    I = i - 1, J = j + 1;
    while (I >= 0 && J < w && table[I][J] == actual) {
        cont++;
        if (cont >= n)
            return true;
        I--;
        J++;
    }

    return false;
}

bool Game::isColumnFilled(int column) {
    return piecePosition[column] < 0;
}

void Game::print() {
    cout << "  ";
    for (int i = 1; i <= w; i++)
        cout << i << " ";

    cout << endl;
    for (int i = 0; i < h; i++) {
        cout << "| ";
        for (int j = 0; j < w; j++) {
            cout << table[i][j] << " ";
        }
        cout << "|";
        cout << endl;
    }
    cout << "+ ";
    for (int k = 0; k < w; k++)
        cout << "_ ";
    cout << "+";
    cout << endl;
}