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

int score_and_print(Card *hand, int count)
{
    int score = 0;
    int suit_map[NUM_SUITS] = {0,0,0,0};
    int rank_map[NUM_RANKS] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

    int i = 0;
    int j = 0;

    printf("\n");

    // Count Flushes
    //    A Flush is 4 or more cards of the same suit.
    //
    //    This algorithm simply uses a map from suits to counts, 
    //    any value at least four is added to the score
    for(i = 0; i < count; ++i) {
        suit_map[hand[i].suit] += 1;  // you could add the card here
    }
    for(i = 0; i < NUM_SUITS; ++i) {
        if(suit_map[i] >= FLUSH_MIN) {
            score += suit_map[i];
            printf("Flush for %d: ", suit_map[i]);

            // find all cards of that suit
            Suit suit = (Suit)i;
            for(j = 0; j < count; ++j) {
                if(hand[j].suit == suit) print_card(hand[j]);
            }
            printf("\n");
        }
    }

    // Count Pairs
    //    A Pair is two cards with the same rank.
    //
    //        1   2   3   4
    //    1      12  13  14
    //    2          23  24
    //    3              34
    //    4  
    //
    for(i = 0; i < count; ++i) {
        for(j = i+1; j < count; ++j) {
            if(hand[i].rank == hand[j].rank) {
                printf("Pair for 2: ");
                print_card(hand[i]);
                print_card(hand[j]);
                printf("\n");

                score += 2;
            }
        }
    }

    // Runs
    // Fifteens

    printf("\nScore: %d\n", score);
    return score;
}

