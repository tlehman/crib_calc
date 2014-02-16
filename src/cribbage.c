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

int compare_cards(const void *a, const void *b)
{
    return ((Card *)b)->rank <= ((Card *)a)->rank;
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

    // Compute all subsets
    //
    //     To score the hand, we need to look at all combinations of cards.
    //     For example, for a hand of three cards:  5♣  10♥  5♥  we must 
    //     consider all 2^3 - 1 = 7 non-empty subsets:
    //        Hand         | Bits |
    //        -------------|------|
    //                 5♥  | 001  |
    //            10♥      | 010  |
    //            10♥  5♥  | 011  |
    //        5♣           | 100  |
    //        5♣       5♥  | 101  |
    //        5♣  10♥      | 110  |
    //        5♣  10♥  5♥  | 111  |
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
        qsort(subhand, count_ones(i), sizeof(Card), compare_cards);
        print_cards(subhand, count_ones(i));

        sum = 0;
        for(j = 0; j < k; ++j) {
            sum += rank_val(subhand[j].rank);
        }

    }

    printf("\nScore: %d\n", score);
    return score;
}

