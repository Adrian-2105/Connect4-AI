#include <iostream>

#include "../include/Game.h"
#include "../include/MinimaxAI.h"

#include <SFML/Graphics.hpp>
using namespace sf;

#define MAX_FPS 10

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define NUM_CONNECTED_PIECES 4
#define NUM_ROWS 7
#define NUM_COLUMNS 8

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void drawScreen(RenderWindow &window, const Game &game);

int DIAMETER;

using namespace std;

int main() {

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Connect4-AI");
    window.setFramerateLimit(MAX_FPS);

    Game game(NUM_CONNECTED_PIECES, NUM_COLUMNS, NUM_ROWS);
    MinimaxAI bot1, bot2;

    game.init();

    int result, n;
    DIAMETER = WINDOW_WIDTH / NUM_COLUMNS;

    Event event{};
    drawScreen(window, game);
    while (window.isOpen() && ((result = game.isFinished()) == UNFINISHED)) {

        bool clicked = false;
        while (window.pollEvent(event) || !clicked) {
            if (event.type == Event::Closed) {
                window.close();
                return 0;
            }
            else if (event.type == Event::MouseButtonPressed) {
                int selected = event.mouseButton.x / DIAMETER;
                if (selected >= 0 && selected < game.getWidth()) {
                    game.insertPiece(PIECE_X, event.mouseButton.x / DIAMETER);
                    clicked = true;
                }
            }
        }

        /*
        n = bot1.nextMove(*game.clone(), PIECE_X);
        game.insertPiece(PIECE_X, n);

        sleep(1);
         */
        drawScreen(window, game);

        if ((result = game.isFinished()) != UNFINISHED)
            break;

        n = bot2.nextMove(*game.clone(), PIECE_O);

        game.insertPiece(PIECE_O, n);

        drawScreen(window, game);
        //sleep(1);
    }

    if (result == WIN_X)
        cout << "X WIN!!!\n";
    else if (result == WIN_O)
        cout << "O WIN!!!\n";
    else
        cout << "Draw\n";

    cin >> n;
}

void drawScreen(RenderWindow &window, const Game &game) {
    window.clear(Color::Blue);
    for (int i = 0; i < game.getHeight(); i++) {
        for (int j = 0; j < game.getWidth(); j++) {
            Color c = game.at(i, j) == EMPTY ? Color::White : game.at(i, j) == PIECE_X ? Color::Red : Color::Yellow;
            CircleShape cs(DIAMETER / 2);
            cs.setFillColor(c);
            cs.setPosition(j * DIAMETER, i * DIAMETER);
            window.draw(cs);
        }
    }
    window.display();
}
