#include "cards.h"

int main(int argc, char *argv[])
{
    int i = 1;
    Card hand[argc];

    draw_random_cards(hand, argc);

    for(i = 1; i < argc; ++i) {
        init_card_from_string(&hand[i], argv[i]);
        print_card(hand[i]);
    }

    printf("\n");
    return 0;
}

