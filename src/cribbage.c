/** Cribbage Calculator: count up cribbage points given a hand
    Copyright (C) 2013 Tobi Lehman

    cribbage.h uses cards.h and implements the rules for counting 
    points in the game of cribbage.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see [http://www.gnu.org/licenses/].  */
#include "cribbage.h"
#include "debug.h"

int score_and_print(Card *c, int count)
{
    int score = 0;
    int suit_map[NUM_SUITS] = {0};
    int rank_map[NUM_RANKS] = {0};

    PRINT_ARRAY(suit_map, NUM_SUITS);
    PRINT_ARRAY(rank_map, NUM_RANKS);

    // flushes
    // pairs
    // runs
    // fifteens
    return score;
}

