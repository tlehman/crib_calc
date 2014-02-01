/** Cribbage Calculator: count up cribbage points given a hand
    Copyright (C) 2013 Tobi Lehman

 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

// ♣  ♥  ♠  ♦  
enum suit { club, heart, spade, diamond };
typedef unsigned int Rank;
typedef enum suit Suit;
static const int NUM_RANKS = 13;
static const int NUM_SUITS = 4;

struct card
{
    Rank rank;
    Suit suit;
};
typedef struct card Card;

const char *suit_to_s(Suit s);
const char *rank_to_s(Rank r);


void print_card(Card c);
void print_cards(Card *c, int count);
void draw_random_cards(Card c[], int count);
void init_card_from_string(Card *c, const char *s);
void init_cards_from_strings(Card *c, int count, const char *s[]);

