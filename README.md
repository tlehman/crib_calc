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

## Todo
 - Fix segfault when lower-case ranks are entered
 - Finish score and print function
 - Make style consistent

