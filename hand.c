#include "cards.h"

int main(int argc, char *argv[])
{
    int i = 0;
    int count = 6;
    Card hand[count];

    draw_random_cards(hand, count);

    for(i = 0; i < count; ++i) {
        print_card(hand[i]);
    }

    return 0;
}

