#include <iostream>

#include "../include/Game.h"
#include "../include/MinimaxAI.h"

using namespace std;

int main() {

    Game game(4, 8, 7);
    MinimaxAI bot;

    game.init();

    int result, n;

    while ((result = game.isFinished()) == UNFINISHED) {
        //cout << string(100, '\n');
        game.print();

        cout << "X move: \n";

        cin >> n;

        game.insertPiece(PIECE_X, n - 1);

        if ((result = game.isFinished()) != UNFINISHED)
            break;

        cout << string(100, '\n');
        game.print();

        cout << "O move: \n";

        n = bot.nextMove(*game.clone(), PIECE_O);

        game.insertPiece(PIECE_O, n);
    }

    cout << endl;

    cout << string(100, '\n');

    game.print();

    if (result == WIN_X)
        cout << "X WIN!!!\n";
    else if (result == WIN_O)
        cout << "O WIN!!!\n";
    else
        cout << "Draw\n";
}