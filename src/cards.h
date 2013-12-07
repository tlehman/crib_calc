/** Cribbage Calculator: count up cribbage points given a hand
    Copyright (C) 2013 Tobi Lehman

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see [http://www.gnu.org/licenses/].
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

