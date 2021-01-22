#ifndef LINEUP4_MINIMAXAI_H
#define LINEUP4_MINIMAXAI_H

#include "AI.h"
#include "Game.h"

class MinimaxAI : public AI {
public:
    int nextMove(Game & game, char piece) override;
};


#endif
