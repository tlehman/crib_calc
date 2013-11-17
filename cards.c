#include "cards.h"
#include <stdio.h>

const char *suit_to_s(Suit s)
{
    const char *retval;
    switch(s) {
        case club:
            retval = "♣";
            break;
        case heart:
            retval = "♥";
            break;
        case spade:
            retval = "♠";
            break;
        case diamond:
            retval = "♦";
            break;
        default:
            retval = "\0";
    }
    return retval; 
}

void print_card(Card c)
{
    printf("%d%s ", c.rank, suit_to_s(c.suit));
}

void draw_random_cards(Card c[], int count)
{
    int i = 0;
    for(i = 0; i < count; ++i) {
    }
}

