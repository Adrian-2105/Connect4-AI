#ifndef GAME_H
#define GAME_H

#define EMPTY     '.'
#define PIECE_X   'X'
#define PIECE_O   'O'

#define UNFINISHED 0
#define TABLE_FULL 1
#define WIN_X 2
#define WIN_O 3

class Game {
private:
    char **table;
    int *piecePosition;
    int width, height;
    int nPiecesConnected;

    bool checkHorizontal(int i, int j);

    bool checkVertical(int i, int j);

    bool checkDiagonalUpToDown(int i, int j);

    bool checkDiagonalDownToUp(int i, int j);

public:
    Game(int n, int w, int h);

    ~Game();

    // To access the table with game[i][j]
    inline char *operator[](int index) const {
        return table[index];
    }

    inline int getWidth() const {
        return width;
    }

    inline int getHeight() const {
        return height;
    }

    inline char at(int i, int j) const {
        return table[i][j];
    }

    Game *clone();

    void init();

    bool insertPiece(char piece, int column);

    int isFinished();

    bool isColumnFilled(int column);

    void print();
};

#endif