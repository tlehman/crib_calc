/** Cribbage Calculator: count up cribbage points given a hand
    Copyright (C) 2013 Tobi Lehman

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

/** rank_val takes:
    @r     Rank

    And returns the value (score) for that rank.
 */
int rank_val(Rank r)
{
    if((int)r > 10) return 10;
    return (int)r;
}

/** rank_val takes:
    @r     Rank

    And returns the string representation for that rank.
 */
const char *rank_to_s(Rank r)
{
    unsigned i = (unsigned)r;
    if(i < 1 || i >= 13) return "\0";
    const char *ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    return ranks[i-1];
}

/** s_to_rank takes:
    @s      const char[]

    And maps strings matching /^(A|[2-9JQK]|10)$/i to a Rank.
 */
Rank s_to_rank(const char s[])
{
    unsigned int i = 0;
    const char *ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    for(i = 0; i < sizeof(ranks); ++i) {
        if(toupper(s[0]) == ranks[i][0]) return (Rank)(i+1);
    }
    printf("error: '%s' is not a rank", s);
    exit(-1);
}

/** s_to_suit takes:
    @s      const char[]

    And maps strings matching /^chsd$/i to a Suit.
 */
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

/** print_card takes:
    @c      Card

    And outputs the rank and suit
 */
void print_card(Card c)
{
    printf("%s%s  ", rank_to_s(c.rank), suit_to_s(c.suit));
}

/** print_cards takes:
    @c      Card*
    @count  int

    And outputs the rank and suit (formatted), followed by 
    a newline.
 */
void print_cards(Card *c, int count)
{
    int i = 0;
    for(i = 0; i < count; ++i) {
        print_card(c[i]);
    }
    printf("\n");
}

int in_hand(Card hand[], int count, Suit s, Rank r)
{
    int i = 0;

    // check that (s,r) hasn't already been chosen
    for(i = 0; i < count; ++i) {
        if(hand[i].rank == r && hand[i].suit == s) {
            return 1;
        }
    }
    return 0;
}

/** draw_random_cards takes:
    @c      Card[]
    @count  int

    Where c has count number of elements, and then initializes
    all count cards with random values.
 */
void draw_random_cards(Card c[], int count)
{
    srand(time(NULL));
    int i = 0;
    Suit s;
    Rank r;

    for(i = 0; i < count; ++i) {
        do {
          s = (Suit)(rand()%4);
          r = (Rank)(rand()%13);

        } while( in_hand(c, i-1, s, r) );

        c[i].suit = s;
        c[i].rank = r;
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

    int max_len = 4; // the max length is 4 == strlen("10C")+1 (the null char)
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

/** init_cards_from_string takes:
    @c      Card*
    @count  int
    @s      const char*[]

    And maps the string @c matching /^(([A2-9JKQ]|10)([CHSD]) )+$/ to a 
    corresponding array of Cards of size @count.
 */
void init_cards_from_strings(Card *c, int count, const char *s[])
{
    int i = 0;
    for(i = 0; i < count; ++i) {
        init_card_from_string(c + i, s[i]);

        if(in_hand(c, i, c[i].suit, c[i].rank)) {
            printf("error: duplicates not allowed\n");
            exit(-1);
        }
    }
}

