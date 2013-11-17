#include <stdio.h>
#include <stdlib.h>

// ♣  ♥  ♠  ♦  
enum suit { club, heart, spade, diamond };
typedef unsigned int Rank;
typedef enum suit Suit;

struct card
{
    Rank rank;
    Suit suit;
};

typedef struct card Card;

const char *suit_to_s(Suit s);
const char *rank_to_c(Rank r);

void print_card(Card c);
void draw_random_cards(Card c[], int count);

