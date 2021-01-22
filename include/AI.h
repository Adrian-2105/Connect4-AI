#ifndef LINEUP4_AI_H
#define LINEUP4_AI_H

#include "Game.h"

class AI {
public:
    virtual int nextMove(Game & game, char piece) = 0;
};

#endif
