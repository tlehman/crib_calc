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

/** is_flush takes
    @c      Card[]
    @count  int

    and returns 1 if is flush, 0 otherwise.

    A flush in cribbage is 5 or more cards of the same suit.
 */
int is_flush(Card c[], int count)
{
    if(count < FLUSH_MIN) return 0;

    Suit s = c[0].suit;
    int i;

    for(i = 0; i < count; i++) {
        if(c[i].suit != s) return 0;
    }
    return 1;
}

/** is_pair takes
    @c      Card[]
    @count  int

    and returns 1 if is pair, 0 otherwise.
 */
int is_pair(Card c[], int count)
{
    if(count != 2) return 0;

    return (c[0].rank == c[1].rank);
}

/** is_run takes
    @c      Card[]
    @count  int

    and returns 1 if c's ranks are in consecutive order.
    (assumes c is sorted by rank)
 */
int is_run(Card c[], int count)
{
    if(count < 3) return 0;
    int i;
    int rdiff;

    for(i = 1; i < count; i++) {
        rdiff = (int)c[i].rank - (int)c[i-1].rank;
        if(rdiff != 1) return 0;
    }
    return 1;
}

/** is_fifteen takes
    @c      Card[]
    @count  int

    and returns 1 if c's ranks sum up to 15, otherwise it returns 0
    (assumes c is sorted by rank)
 */
int is_fifteen(Card c[], int count)
{
    int i;
    int sum = 0;

    for(i = 0; i < count; i++) {
        sum += rank_val(c[i].rank);
    }
    return (sum == 15);
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
int score_and_print(Card hand[], int count)
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
    int ones = 0;

    qsort(hand, count, sizeof(Card), compare_cards);
    for(i = 1; i < TWO_TO_THE(count); ++i) {
        k = 0;
        ones = count_ones(i);

        // select subset of hand using bits
        Card subhand[ones];

        for(j = 1; j < sizeof(unsigned int)*8; ++j) {
            if(JTH_BIT(i, j)) {
                subhand[k] = hand[j-1];
                k += 1;
            }
        }

        if( is_flush(subhand, ones) ) {
            printf("Flush for %d: ", ones);
            print_cards(subhand, ones);
            score += ones; // TODO: only pick largest flush
        }
        if( is_run(subhand, ones) ) {
            printf("Run of %d for %d: ", ones, ones);
            print_cards(subhand, ones);
            score += ones; // TODO: only pick largest run
        }
        if( is_pair(subhand, ones) ) {
            printf("Pair for 2: ");
            print_cards(subhand, ones);
            score += 2;
        }
        if( is_fifteen(subhand, ones) ) {
            printf("Fifteen for 2: ");
            print_cards(subhand, ones);
            score += 2;
        }
    }

    printf("\nScore: %d\n", score);
    return score;
}

