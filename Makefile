CFLAGS=-Wall -g

all: hand

hand: cards.o hand.o
	cc tmp/*.o -o bin/hand

cards.o:
	cc -c src/cards.c -o tmp/cards.o

hand.o:
	cc -c src/hand.c -o tmp/hand.o

clean:
	rm bin/*
	rm tmp/*
	rm -rf *.dSYM

