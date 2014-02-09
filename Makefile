CFLAGS=-Wall -g3

all: prep hand

prep:
	if [ -d bin ]; then echo '' > /dev/null; else mkdir bin; fi
	if [ -d tmp ]; then echo '' > /dev/null; else mkdir tmp; fi

hand: cribbage.o cards.o hand.o
	cc -g3 tmp/*.o -o bin/hand

cribbage.o:
	cc -g3 -c src/cribbage.c -o tmp/cribbage.o

cards.o:
	cc -g3 -c src/cards.c -o tmp/cards.o

hand.o:
	cc -g3 -c src/hand.c -o tmp/hand.o

clean:
	rm bin/*
	rm tmp/*
	rm -rf *.dSYM

