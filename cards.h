
// ♣  ♥  ♠  ♦  
enum suit { club, heart, spade, diamond };
typedef int Rank;
typedef enum suit Suit;

struct card
{
    Rank rank;
    Suit suit;
};

typedef struct card Card;

const char *suit_to_s(Suit s);
void print_card(Card c);
void draw_random_cards(Card c[], int count);

