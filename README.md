# Cribbage calculator in C

## Compilation:

Just run:

```
  make
```

## Usage:

To use this program, make sure you are in the root directory of this project, 
then enter something like this:

```
  $ bin/hand 2h 2d 2c 2s
  2♥  2♦  2♣  2♠
```

## Note
Make sure that you are using UTF-8.

## Implementation

The `Card` is a struct:

```
struct card
{
    Rank rank;
    Suit suit;
};
```

Where `Rank` is an `unsigned int` and `Suit` is an enum type:

```
enum suit { club, heart, spade, diamond };
```

To score the hand, we need to look at all combinations of cards.
For example, for a hand of three cards:  5♣  10♥  5♥  we must 
consider all 2^3 - 1 = 7 non-empty subsets:

```
   Hand         | Bits |
   -------------|------|
            5♥  | 001  |
       10♥      | 010  |
       10♥  5♥  | 011  |
   5♣           | 100  |
   5♣       5♥  | 101  |
   5♣  10♥      | 110  |
   5♣  10♥  5♥  | 111  |
```

There is a well known correspondence betweeen subsets and binary 
representations of integers, illustrated in the 'Bits' column above.
Using this correspondence, we can enumerate all 2^n subsets by looping
an integer from 0 to (2^n - 1) and identifying the bits that are one 
with the subset membership relation.

For each subset of cards, the following are checked:
 - Pairs
 - Runs of 3 or higher
 - Flushes of 4 or more cards
 - Fifteens


## Todo
 - Make style consistent
 - Count more than one run (if exists)

