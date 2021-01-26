#ifndef GAME_H
#define GAME_H

typedef char Piece;
typedef unsigned int uint;

// Type of squares on the table
#define EMPTY           '.'
#define PIECE_PLAYER_1  'X'
#define PIECE_PLAYER_2  'O'

// GameStatus of the game
enum GameStatus {
    UNFINISHED = 0, TABLE_FULL, WIN_PLAYER_1, WIN_PLAYER_2
};

class Game {
private:
    // Properties
    Piece **table;
    uint *piecePosition;
    uint width, height;
    uint nPiecesConnected;
    GameStatus status;

    // Helper methods
    void changeStatus(uint i, uint j);

public:
    // Constructor
    Game(uint nPiecesConnected, uint width, uint height);

    // Destroyer
    ~Game();

    // To access the table with game[i][j]
    inline Piece *operator[](uint index) const {
        return table[index];
    }

    /* Getters */
    inline uint getWidth() const {
        return width;
    }

    inline uint getHeight() const {
        return height;
    }

    inline uint getNPiecesConnected() const {
        return nPiecesConnected;
    }

    inline GameStatus getGameStatus() const {
        return status;
    }

    inline Piece at(uint i, uint j) const {
        return table[i][j];
    }

    /* Main methods */
    void init();

    bool insertPiece(Piece piece, uint column);

    bool isColumnFilled(uint column);

    void print();

    Game *clone();
};

#endif