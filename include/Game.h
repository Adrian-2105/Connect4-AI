#ifndef GAME_H
#define GAME_H

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
    char **table;
    int *piecePosition;
    int width, height;
    int nPiecesConnected;

public:
    // Constructor
    Game(int nPiecesConnected, int width, int height);

    // Destroyer
    ~Game();

    // To access the table with game[i][j]
    inline char *operator[](int index) const {
        return table[index];
    }

    /* Getters */
    inline int getWidth() const {
        return width;
    }

    inline int getHeight() const {
        return height;
    }

    inline char at(int i, int j) const {
        return table[i][j];
    }

    /* Main methods */
    void init();

    GameStatus getStatus();

    bool insertPiece(char piece, int column);

    bool isColumnFilled(int column);

    void print();

    Game *clone();
};

#endif