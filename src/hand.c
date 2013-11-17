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

