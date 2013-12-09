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
    int suit_map[4]  = {0,0,0,0};
    int rank_map[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

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

    // Count Runs
    //    A Run is a sequence of 3 or more cards with contiguous ranks.
    //
    //    To find runs, we keep track of these data:
    //      run_length    int
    //      multiplicity  int
    //      index         int
    //      rank_map      int[13]
    //
    //    Before we introduce the algorithm, it is helpful to see an 
    //    example, suppose our hand is:
    //        9♥  8♥  6♣  7♠  8♦  8♣
    //    we start by computing rank_map: 
    //        A 2 3 4 5 6 7 8 9 10 J K Q
    //        0 0 0 0 0 1 1 3 1  0 0 0 0
    //                  ^ scan until the first nonzero value is found, 
    //                    then scan until you hit the next zero value:
    //        A 2 3 4 5 6 7 8 9 10 J K Q
    //        0 0 0 0 0 1 1 3 1  0 0 0 0
    //                           ^ at this point you should have run_length = 4
    //                             and 4 >= 3, so it counts as a run.
    //                             Notice that you have three runs:
    //                                  6♣  7♠  8♦  9♥  
    //                                   "   "  8♥   "
    //                                   "   "  8♣   "
    //                             This is why multiplicity is multiplied 
    //                             with run_length to compute the score.
    //
    //    The algorithm goes like this:
    //      Initialize index        = 0
    //                 multiplicity = 1
    //                 run_length   = 0
    //      Scan from left to right (increasing index)
    //
    //      Loop index 0 to 13
    //          if rank_map[index] > 0
    //              run_length += 1
    //              multiplicity *= rank_map[index]
    //          else
    //              if run_length >= 3
    //                  display (run_length, multiplicity * run_length)
    //              endif
    //              run_length = 0
    //              multiplicity = 1
    //          endif
    //      End Loop
    //

    // Initialize rank_map
    for(i = 0; i < count; ++i) {
        rank_map[(int)hand[i].rank] += 1;
    }
    PRINT_ARRAY(rank_map, 13);

    // Find the first flush (good enough for now)
    int rlen = 0;
    int mult = 1;

    for(i = 0; i < 13; ++i) {
        if(rank_map[i] > 0) {
            rlen += 1;
            mult *= rank_map[i];
        } else {
            if(rlen >= 3) {
                // Run found!
                printf("Run of %d for %d\n", rlen, mult*rlen);
                //for(j = (i-rlen); j < i; ++j) print_card();  How to find cards corresponding to run?
            }
            // reset Run data at sight of zero value
            rlen = 0;
            mult = 1;
        }
    }

    // Fifteens

    printf("\nScore: %d\n", score);
    return score;
}

