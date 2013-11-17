#include "cards.h"

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

const char *rank_to_c(Rank r)
{
    unsigned i = (unsigned)r;
    if(i >= 13) return "\0";

    const char *ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

    return ranks[i];
}

void print_card(Card c)
{
    printf("%s%s ", rank_to_c(c.rank), suit_to_s(c.suit));
}

void draw_random_cards(Card c[], int count)
{
    int i = 0;
    for(i = 0; i < count; ++i) {
        c[i].suit = (Suit)(arc4random()%4);
        c[i].rank = (Rank)(arc4random()%13);
    }
}

