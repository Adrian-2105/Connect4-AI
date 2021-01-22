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
    char** table;
    int* piecePosition;
    int w, h;
    int n;

    bool checkHorizontal(int i, int j);
    bool checkVertical(int i, int j);
    bool checkDiagonalUpToDown(int i, int j);
    bool checkDiagonalDownToUp(int i, int j);
public:
    Game(int n, int w, int h);
    ~Game();

    Game* clone();

    int getWidth() const;

    int getHeight() const;

    char at(int i, int j) const;

    void init();

    bool insertPiece(char piece, int column);

    int isFinished();

    bool isColumnFilled(int column);

    void print();
};

#endif