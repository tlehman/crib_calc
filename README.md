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

The algorithm to calculate the score starts by taking an array of Cards, then
counts flushes by computing a frequency map `{♣ => 2, ♥ => 0, ♠ => 4, ♦ => 0}`.

Given that map, the algorithm then finds all suits whose frequencies are at 
least 4, then prints then out.

After the flushes are counted, then we move on to pairs, where the unique
pairs are computed using a 2-d matrix of indices like this:

```
      12  13  14  15
          23  24  25
              34  35
                  45
```

The above matrix is implemented as a nested loop where the inner index `j` is 
always greater than the outer index `i`.

## Todo
 - Finish score and print function
 - Make style consistent
 - Disallow duplicate cards
 - Count more than one run (if exists)

