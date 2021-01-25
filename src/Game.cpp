#include <iostream>
#include "../include/Game.h"

using namespace std;

Game::Game(int _nPiecesConnected, int _width, int _height) :
        nPiecesConnected(_nPiecesConnected),
        width(_width),
        height(_height) {

    char *auxTable = new char[width * height];

    table = new char *[height];

    for (int i = 0; i < height; i++)
        table[i] = &auxTable[i * width];

    piecePosition = new int[width];
}

Game::~Game() {
    delete[] table[0];
    delete[] table;
    delete[] piecePosition;
}

Game *Game::clone() {
    Game *newGame = new Game(nPiecesConnected, width, height);

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            newGame->table[i][j] = table[i][j];

    for (int j = 0; j < width; j++)
        newGame->piecePosition[j] = piecePosition[j];

    return newGame;
}

void Game::init() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            table[i][j] = EMPTY;

    for (int i = 0; i < width; i++)
        piecePosition[i] = height - 1;
}

bool Game::insertPiece(char piece, int column) {
    if (piecePosition[column] < 0)
        return false;

    table[piecePosition[column]][column] = piece;
    piecePosition[column]--;
    return true;
}

int Game::isFinished() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (table[i][j] != EMPTY && (checkHorizontal(i, j) || checkVertical(i, j) || checkDiagonalUpToDown(i, j) ||
                                         checkDiagonalDownToUp(i, j)))
                return table[i][j] == PIECE_X ? WIN_X : WIN_O;

    for (int i = 0; i < width; i++)
        if (piecePosition[i] >= 0)
            return UNFINISHED;
    return TABLE_FULL;
}

bool Game::checkHorizontal(int i, int j) {
    char actual = table[i][j];
    int cont = 1;

    int J = j + 1;
    while (J < width && table[i][J] == actual) {
        cont++;
        if (cont >= nPiecesConnected)
            return true;
        J++;
    }

    return false;
}

bool Game::checkVertical(int i, int j) {
    char actual = table[i][j];
    int cont = 1;

    int I = i + 1;
    while (I < height && table[I][j] == actual) {
        cont++;
        if (cont >= nPiecesConnected)
            return true;
        I++;
    }

    return false;
}

bool Game::checkDiagonalUpToDown(int i, int j) {
    char actual = table[i][j];
    int cont = 1;
    int I = i + 1, J = j + 1;
    while (I < height && J < width && table[I][J] == actual) {
        cont++;
        if (cont >= nPiecesConnected)
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
    while (I < height && J >= 0 && table[I][J] == actual) {
        cont++;
        I++;
        J--;
    }

    I = i - 1, J = j + 1;
    while (I >= 0 && J < width && table[I][J] == actual) {
        cont++;
        if (cont >= nPiecesConnected)
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
    for (int i = 1; i <= width; i++)
        cout << i << " ";

    cout << endl;
    for (int i = 0; i < height; i++) {
        cout << "| ";
        for (int j = 0; j < width; j++) {
            cout << table[i][j] << " ";
        }
        cout << "|";
        cout << endl;
    }
    cout << "+ ";
    for (int k = 0; k < width; k++)
        cout << "_ ";
    cout << "+";
    cout << endl;
}