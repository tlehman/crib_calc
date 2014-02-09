/** Cribbage Calculator: count up cribbage points given a hand
    Copyright (C) 2013 Tobi Lehman

    cribbage.h uses cards.h and implements the rules for counting 
    points in the game of cribbage.
*/
#include "cards.h"

#define 2_TO_THE(POWER) (1 << POWER)

static const int FLUSH_MIN = 4;

int score_and_print(Card *c, int count);

