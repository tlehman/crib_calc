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

const char *rank_to_s(Rank r)
{
    unsigned i = (unsigned)r;
    if(i >= 13) return "\0";
    const char *ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    return ranks[i];
}

Rank s_to_rank(const char s[])
{
    unsigned int i = 0;
    const char *ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    for(i = 0; i < sizeof(ranks); ++i) {
        if(s[0] == ranks[i][0]) return (Rank)i;
    }
    printf("error: '%s' is not a rank", s);
    exit(-1);
}

Suit s_to_suit(const char s[])
{
    switch(s[0]) {
    case 'c':
    case 'C':
        return club;
        break;
    case 'h':
    case 'H':
        return heart;
        break;
    case 's':
    case 'S':
        return spade;
        break;
    case 'd':
    case 'D':
        return diamond;
        break;
    default:
        printf("error: '%s' is not a suit", s);
        exit(-1);
    }
} 

void print_card(Card c)
{
    printf("%s%s  ", rank_to_s(c.rank), suit_to_s(c.suit));
}

void print_cards(Card *c, int count)
{
    int i = 0;
    for(i = 1; i < count; ++i) {
        print_card(c[i]);
    }
}

/** draw_random_cards takes:
    @c      Card[]
    @count  int

    Where c has count number of elements, and then initializes
    all count cards with random values.
 */
void draw_random_cards(Card c[], int count)
{
    int i = 0;
    for(i = 0; i < count; ++i) {
        c[i].suit = (Suit)(arc4random()%4);
        c[i].rank = (Rank)(arc4random()%13);
    }
}

/** init_card_from_string takes:
    @c      Card *
    @str    const char *

    And attempts to extract the rank and suit from the string,
    assigning the appropriate value to *c
 */
void init_card_from_string(Card *c, const char *str)
{
    char pattern[] = "^([A2-9JKQ]|10)([CHSD])$";
    regex_t reg;

    int max_len = 6; // the max length is 4 == strlen("10C")+1 (the null char)
    char rank_s[max_len];
    char suit_s[max_len];

    /* since there are only two pieces to be extracted from the string,
       the rank and the suit, the number of matches should be two, plus 
       the match for the entire expression */
    size_t n = 2 + 1;
    regmatch_t matches[n];

    // use extended regexes, case insensitive
    if(0 != regcomp(&reg, pattern, REG_EXTENDED | REG_ICASE)) {
        printf("error compiling regex /%s/", pattern);
        exit(-1);
    }

    if(0 != regexec(&reg, str, n, matches, 0)) {
        printf("\nerror parsing card string: %s\n", str);
        exit(-1);
    }

    // copy the match results into temporary strings
    strncpy(rank_s, (str + matches[1].rm_so), matches[1].rm_eo - matches[1].rm_so);
    strncpy(suit_s, (str + matches[2].rm_so), matches[2].rm_eo - matches[2].rm_so);

    c->rank = s_to_rank(rank_s);
    c->suit = s_to_suit(suit_s);
}

void init_cards_from_strings(Card *c, int count, const char *s[])
{
    int i = 1;
    for(i = 1; i < count; ++i) {
        init_card_from_string(c + i, s[i]);
    }
}

