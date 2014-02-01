/** Cribbage Calculator: count up cribbage points given a hand
    Copyright (C) 2013 Tobi Lehman
 */
#include "cribbage.h"

int main(int argc, const char *argv[])
{
    int i = 1;
    int count = argc;
    Card *hand;

    if(1 == argc) {
        count = 6; // default cribbage hand size
        hand = (Card *)malloc(sizeof(Card)*count);

        printf("no input, drawing six random cards\n");

        draw_random_cards(hand, count);
    } else {
        count = argc - 1;
        hand = (Card *)malloc(sizeof(Card)*count);

        init_cards_from_strings(hand, count, argv+1);
    }

    print_cards(hand, count);

    score_and_print(hand, count);

    if(hand) free(hand);
    return 0;
}

