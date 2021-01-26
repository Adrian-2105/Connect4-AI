#include <iostream>
#include <cstring>
#include "../include/Game.h"

//#define DEBUG

using namespace std;

Game::Game(uint _nPiecesConnected, uint _width, uint _height) :
        nPiecesConnected(_nPiecesConnected),
        width(_width),
        height(_height),
        status(UNFINISHED) {

    // We use a contiguous array to minimize cache misses
    auto *auxTable = new Piece[width * height];

    // And store the pointer of each row
    table = new Piece *[height];
    for (uint i = 0; i < height; i++)
        table[i] = &auxTable[i * width];

    // It's an auxiliary array to make the inserts more efficiently
    piecePosition = new uint[width];

    // Initialize the game
    init();
}

Game::~Game() {
    delete[] table[0];
    delete[] table;
    delete[] piecePosition;
}

void Game::init() {
    // Set the status to unfinished
    status = UNFINISHED;

    // Initialize the matrix to EMPTY
    memset(table[0], EMPTY, width * height);

    // Initialize the helper array
    for (uint j = 0; j < width; j++)
        piecePosition[j] = height - 1;
}

bool Game::insertPiece(Piece piece, uint column) {
    // Checks if we can insert a piece in that column
    if (isColumnFilled(column))
        return false;

    // If we can, we add the piece to the table
    uint i = piecePosition[column], j = column;
    table[i][j] = piece;

    // Update the status
    changeStatus(i, j);

    // Update the auxiliary array
    piecePosition[column]--;

    return true;
}

bool Game::isColumnFilled(uint column) {
    return piecePosition[column] > height;
}

void Game::print() {
    // Header
    cout << "  ";
    for (uint k = 1; k <= width; k++)
        cout << k << " ";
    cout << endl;

    // Body
    for (uint i = 0; i < height; i++) {
        cout << "| ";
        for (uint j = 0; j < width; j++)
            cout << table[i][j] << " ";
        cout << "|" << endl;
    }

    // Footer
    cout << "+ ";
    for (uint k = 0; k < width; k++)
        cout << "_ ";
    cout << "+" << endl;
}

Game *Game::clone() {
    // We create a new Game
    Game *newGame = new Game(nPiecesConnected, width, height);

    // And copy the both arrays
    memcpy(newGame->table[0], table[0], width * height);
    memcpy(newGame->piecePosition, piecePosition, width * sizeof(uint));

    // Return the new Game
    return newGame;
}

void Game::changeStatus(uint i, uint j) {
    // Check if any player has won the game
    {
        Piece piece = table[i][j];

#define NUM_DIRECTIONS 8
        // Auxiliary array to store the number of pieces in each direction
        uint cont[NUM_DIRECTIONS >> 1];
        memset(cont, 0, sizeof(cont));

        // Auxiliary arrays to go through all directions (horizontal, vertical and both diagonals)
        int x[] __attribute__ ((__aligned__(64))) = {1, -1,  0,  0,  1, -1, -1,  1};
        int y[] __attribute__ ((__aligned__(64))) = {0,  0,  1, -1,  1, -1,  1, -1};

        // Loop through each possible direction
        for (uint k = 0; k < NUM_DIRECTIONS; k++) {
            uint kAux = k / 2;
            // Loop counting the pieces that are equal to the piece target
            for (uint I = i + y[k], J = j + x[k]; I < height && J < width && table[I][J] == piece; I += y[k], J += x[k]) {
                cont[kAux]++;
            }
            // Check if the counter has exceeded the number of pieces to win
            if (cont[kAux] + 1 >= nPiecesConnected) {
                status = piece == PIECE_PLAYER_1 ? WIN_PLAYER_1 : WIN_PLAYER_2;
                return;
            }
        }

#ifdef DEBUG
        cout << "Horizontal: " << cont[0] + 1 << endl;
        cout << "Vertical: " << cont[1] + 1 << endl;
        cout << "Diagonal Left-Right: " << cont[2] + 1 << endl;
        cout << "Diagonal Right-Left: " << cont[3] + 1 << endl;
#endif

#undef NUM_DIRECTIONS
    }

    // Otherwise, check if the game is not finished yet
    for (uint J = 0; J < width; J++)
        if (piecePosition[J] >= 0) {
            status = UNFINISHED;
            return;
        }

    // If not, then the game is over because the table is full
    status = TABLE_FULL;
}