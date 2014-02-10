/** Cribbage Calculator: count up cribbage points given a hand
    Copyright (C) 2013 Tobi Lehman

    cribbage.h uses cards.h and implements the rules for counting 
    points in the game of cribbage.
*/
#include "cribbage.h"
#include "debug.h"

unsigned int count_ones(unsigned int bits)
{
    unsigned int v = bits;
    unsigned int c = 0;
    for(c = 0; v; ++c) {
        v &= v-1;
    }
    return c;
}

/** score_and_print takes:
    @hand   Card *
    @count  int

    And calculates the cribbage score:
      - Flushes
      - Pairs
      - Runs
      - Fifteens
 */
int score_and_print(Card *hand, int count)
{
    int score = 0;
    int suit_map[4]  = {0,0,0,0};
    int rank_map[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

    unsigned int i = 0;
    unsigned int j = 0;

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
    //      Loop index 1 to 13
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
                score += mult*rlen;
                //for(j = (i-rlen); j < i; ++j) print_card();  How to find cards corresponding to run?
            }
            // reset Run data at sight of zero value
            rlen = 0;
            mult = 1;
        }
    }

    // Count Fifteens
    //     A Fifteen is any combination of cards whose ranks sum up to 15.
    //
    //     To find fifteens, we need to look at all combinations of cards.
    //     For example, for a hand of three cards:  5♣  10♥  5♥  we must 
    //     consider all 2^3 - 1 = 7 non-empty subsets:
    //        Hand         | Bits | Sum
    //        -------------|------|-----
    //                 5♥  | 001  |  (5)
    //            10♥      | 010  | (10)
    //            10♥  5♥  | 011  | (15)  *
    //        5♣           | 100  |  (5)
    //        5♣       5♥  | 101  | (10)
    //        5♣  10♥      | 110  | (15)  *
    //        5♣  10♥  5♥  | 111  | (20)
    //
    //     There is a well known correspondence betweeen subsets and binary 
    //     representations of integers, illustrated in the 'Bits' column above.
    //     Using this correspondence, we can enumerate all 2^n subsets by looping
    //     an integer from 0 to (2^n - 1) and identifying the bits that are one 
    //     with the subset membership relation.
    // 
    int k = 0;
    int sum = 0;

    for(i = 1; i < TWO_TO_THE(count); ++i) {
        k = 0;

        // select subset of hand using bits
        Card subhand[count_ones(i)];

        for(j = 1; j < sizeof(unsigned int)*8; ++j) {
            if(JTH_BIT(i, j)) {
                subhand[k] = hand[j-1];
                k += 1;
            }
        }

        sum = 0;
        for(j = 0; j < k; ++j) {
            sum += rank_val(subhand[j].rank);
        }
        if(sum == 15) {
            printf("Fifteen for 2: ");
            print_cards(subhand, count_ones(i));
            score += 2;
        }

    }

    printf("\nScore: %d\n", score);
    return score;
}

