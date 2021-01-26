#include <iostream>
#include <cstring>
#include "../include/Game.h"

using namespace std;

Game::Game(int _nPiecesConnected, int _width, int _height) :
        nPiecesConnected(_nPiecesConnected),
        width(_width),
        height(_height) {

    // We use a contiguous array to minimize cache misses
    char *auxTable = new char[width * height];

    // And store the pointer of each row
    table = new char *[height];
    for (int i = 0; i < height; i++)
        table[i] = &auxTable[i * width];

    // It's an auxiliary array to make the inserts more efficiently
    piecePosition = new int[width];

    // Initialize the game
    init();
}

Game::~Game() {
    delete[] table[0];
    delete[] table;
    delete[] piecePosition;
}

void Game::init() {
    // Initialize the matrix to EMPTY
    memset(table[0], EMPTY, width * height);

    // Initialize the helper array
    for (int j = 0; j < width; j++)
        piecePosition[j] = height - 1;
}

GameStatus Game::getStatus() {
    // Check if any player has won the game
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char actual = table[i][j];
            if (actual != EMPTY) {
                // Check vertical
                for (int I = i + 1, cont = 1; I < height && table[I][j] == actual; I++) {
                    cont++;
                    if (cont >= nPiecesConnected)
                        return table[i][j] == PIECE_PLAYER_1 ? WIN_PLAYER_1 : WIN_PLAYER_2;
                }

                // Check horizontal
                for (int J = j + 1, cont = 1; J < width && table[i][J] == actual; J++) {
                    cont++;
                    if (cont >= nPiecesConnected)
                        return table[i][j] == PIECE_PLAYER_1 ? WIN_PLAYER_1 : WIN_PLAYER_2;
                }

                // Check diagonal up left to down right
                for (int I = i + 1, J = j + 1, cont = 1; I < height && J < width && table[I][J] == actual; I++, J++) {
                    cont++;
                    if (cont >= nPiecesConnected)
                        return table[i][j] == PIECE_PLAYER_1 ? WIN_PLAYER_1 : WIN_PLAYER_2;
                }

                // Check diagonal up right to down left
                for (int I = i + 1, J = j - 1, cont = 1; I < height && J >= 0 && table[I][J] == actual; I++, J--) {
                    cont++;
                    if (cont >= nPiecesConnected)
                        return table[i][j] == PIECE_PLAYER_1 ? WIN_PLAYER_1 : WIN_PLAYER_2;
                }

            }
        }
    }

    // Otherwise, check if the game is not finished yet
    for (int j = 0; j < width; j++)
        if (piecePosition[j] >= 0)
            return UNFINISHED;

    // If not, then the game is over because the table is full
    return TABLE_FULL;
}

bool Game::insertPiece(char piece, int column) {
    // Checks if we can insert a piece in that column
    if (isColumnFilled(column))
        return false;

    // If we can, we add the piece to the table and update the auxiliary array
    table[piecePosition[column]][column] = piece;
    piecePosition[column]--;

    return true;
}

bool Game::isColumnFilled(int column) {
    return piecePosition[column] < 0;
}

void Game::print() {
    // Header
    cout << "  ";
    for (int k = 1; k <= width; k++)
        cout << k << " ";
    cout << endl;

    // Body
    for (int i = 0; i < height; i++) {
        cout << "| ";
        for (int j = 0; j < width; j++)
            cout << table[i][j] << " ";
        cout << "|" << endl;
    }

    // Footer
    cout << "+ ";
    for (int k = 0; k < width; k++)
        cout << "_ ";
    cout << "+" << endl;
}

Game *Game::clone() {
    // We create a new Game
    Game *newGame = new Game(nPiecesConnected, width, height);

    // And copy the both arrays
    memcpy(newGame->table[0], table[0], width * height);
    memcpy(newGame->piecePosition, piecePosition, width * sizeof(int));

    // Return the new Game
    return newGame;
}