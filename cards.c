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
    const char *ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

    if(i >= 13) return "\0";

    return ranks[i];
}

Rank s_to_rank(const char s[])
{
    unsigned int i = 0;
    const char *ranks[] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    for(i = 0; i < sizeof(ranks); ++i) {
	if(0 == strcmp(s, ranks[i])) return (Rank)i;
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
    printf("%s%s ", rank_to_s(c.rank), suit_to_s(c.suit));
}

void draw_random_cards(Card c[], int count)
{
    int i = 0;
    for(i = 0; i < count; ++i) {
        c[i].suit = (Suit)(arc4random()%4);
        c[i].rank = (Rank)(arc4random()%13);
    }
}

void init_card_from_string(Card *c, const char *str)
{
    char pattern[] = "([A2-9JKQ]|10)([CHSD])";
    regex_t reg;

    int max = 3; // the max length is 4 == strlen("10C")+1 (the null char)
    char rank_s[max];
    char suit_s[max];

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

    regexec(&reg, str, n, matches, 0);

    // copy the match results into temporary strings
    strncpy(rank_s, (str + matches[1].rm_so), matches[1].rm_eo - matches[1].rm_so);
    strncpy(suit_s, (str + matches[2].rm_so), matches[2].rm_eo - matches[2].rm_so);

    c->rank = s_to_rank(rank_s);
    c->suit = s_to_suit(suit_s);
}

