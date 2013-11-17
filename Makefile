CFLAGS=-Wall -g

hand: hand.o cards.o

cards.o:
	cc -c cards.c

hand.o:
	cc -c hand.c

clean:
	rm -rf *.dSYM
	rm *.o

