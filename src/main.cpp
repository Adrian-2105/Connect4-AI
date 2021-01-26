#include <iostream>
#include <SFML/Graphics.hpp>

#ifdef _WIN32
#include <Windows.height>
#else
#include <unistd.h>
#endif

#include "../include/Game.h"
#include "../include/MinimaxAI.h"

using namespace sf;
using namespace std;

#define MAX_FPS 10

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define NUM_CONNECTED_PIECES 4
#define NUM_ROWS 7
#define NUM_COLUMNS 8

#define VERBOSE

void drawScreen(RenderWindow &window, const Game &game);

uint DIAMETER;

int main() {

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Connect4-AI");
    window.setFramerateLimit(MAX_FPS);

    Game game(NUM_CONNECTED_PIECES, NUM_COLUMNS, NUM_ROWS);
    MinimaxAI bot1, bot2;

    game.init();

    GameStatus result;
    uint n;
    DIAMETER = WINDOW_WIDTH / NUM_COLUMNS;

    Event event{};
    drawScreen(window, game);
#ifdef VERBOSE
    game.print();
#endif
    while (window.isOpen() && ((result = game.getGameStatus()) == UNFINISHED)) {

        bool clicked = false;
        while (window.pollEvent(event) || !clicked) {
            if (event.type == Event::Closed) {
                window.close();
                return 0;
            }
            else if (event.type == Event::MouseButtonPressed) {
                uint selected = event.mouseButton.x / DIAMETER;
                if (selected >= 0 && selected < game.getWidth()) {
                    game.insertPiece(PIECE_PLAYER_1, event.mouseButton.x / DIAMETER);
                    clicked = true;
                }
            }
        }

        /*
        nPiecesConnected = bot1.nextMove(*game.clone(), PIECE_PLAYER_1);
        game.insertPiece(PIECE_PLAYER_1, nPiecesConnected);

        sleep(1);
         */
        drawScreen(window, game);
#ifdef VERBOSE
        game.print();
#endif

        if ((result = game.getGameStatus()) != UNFINISHED)
            break;

        n = bot2.nextMove(*game.clone(), PIECE_PLAYER_2);

        game.insertPiece(PIECE_PLAYER_2, n);

        drawScreen(window, game);
#ifdef VERBOSE
        game.print();
#endif
        //sleep(1);
    }

    if (result == WIN_PLAYER_1)
        cout << "X WIN!!!\n";
    else if (result == WIN_PLAYER_2)
        cout << "O WIN!!!\n";
    else
        cout << "Draw\n";

    cin >> n;
}

void drawScreen(RenderWindow &window, const Game &game) {
    window.clear(Color::Blue);
    for (uint i = 0; i < game.getHeight(); i++) {
        for (uint j = 0; j < game.getWidth(); j++) {
            Color c = game.at(i, j) == EMPTY ? Color::White : game.at(i, j) == PIECE_PLAYER_1 ? Color::Red : Color::Yellow;
            CircleShape cs(DIAMETER / 2);
            cs.setFillColor(c);
            cs.setPosition(j * DIAMETER, i * DIAMETER);
            window.draw(cs);
        }
    }
    window.display();
}
