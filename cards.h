#ifndef _cards_h_
#define _cards_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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
const char *rank_to_s(Rank r);

void print_card(Card c);
void draw_random_cards(Card c[], int count);

void init_card_from_string(Card *c, const char *s);

const char *ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

#endif
