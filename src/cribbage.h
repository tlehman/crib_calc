/** Cribbage Calculator: count up cribbage points given a hand
    Copyright (C) 2013 Tobi Lehman

    cribbage.h uses cards.h and implements the rules for counting 
    points in the game of cribbage.
*/
#include "cards.h"

#define TWO_TO_THE(POWER) (1 << POWER)

#define JTH_BIT(BITS, J)  ((TWO_TO_THE((J-1)) & BITS) != 0)

unsigned int count_ones(unsigned int bits);

static const int FLUSH_MIN = 5;

int score_and_print(Card *c, int count);

