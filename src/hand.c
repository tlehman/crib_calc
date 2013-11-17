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

int main(int argc, const char *argv[])
{
    int i = 1;
    int count = argc;
    Card *hand;

    if(1 == argc) {
        count = 6; // default cribbage hand size
        hand = (Card *)malloc(sizeof(Card)*count);

        printf("no input, drawing six random cards\n");

        draw_random_cards(hand, count);
    } else {
        hand = (Card *)malloc(sizeof(Card));

        init_cards_from_strings(hand, count, argv);
    }

    print_cards(hand, count);

    printf("\n");

    if(hand) free(hand);
    return 0;
}

