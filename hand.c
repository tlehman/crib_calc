#include "cards.h"

int main(int argc, char *argv[])
{
    int i = 1;
    int count = argc - 1;
    Card hand[count];

    draw_random_cards(hand, count);

    for(i = 1; i < count; ++i) {
	init_card_from_string(&hand[i], argv[i]);
        print_card(hand[i]);
    }

    printf("\n");
    return 0;
}

