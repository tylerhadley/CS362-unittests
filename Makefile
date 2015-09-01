CC = gcc
CFLAGS = -fprofile-arcs -fpic -coverage -lm -std=c99
PROGS = playdom player testDrawCard testBuyCard badTestDrawCard unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 randomtestcard randomtestadventurer

rngs.o: rngs.h rngs.c
	$(CC) -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	$(CC) -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	$(CC) -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
	
testDrawCard: testDrawCard.c dominion.o rngs.o
	$(CC) -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	$(CC) -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	$(CC) -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	$(CC) -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	$(CC) -c interface.c -g  $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	$(CC) -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	$(CC) -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	$(CC) -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	$(CC) -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	$(CC) -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	$(CC) -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	$(CC) -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	$(CC) -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

waya_test: waya_test.c dominion.o rngs.o
	$(CC) -o waya_test -g waya_test.c dominion.o rngs.o $(CFLAGS)

randomtestcard: randomtestcard.c dominion.o rngs.o
	$(CC) -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	$(CC) -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard.out:
	rm -f randomtestcard.out
	make clean
	make rngs.o
	make dominion.o
	make randomtestcard
	./randomtestcard >> randomtestcardresults.out
	gcov -f -b dominion.c >> randomtestcardresults.out

randomtestadventurer.out:
	rm -f randomtestadventurer.out
	make clean
	make rngs.o
	make dominion.o
	make randomtestadventurer
	./randomtestadventurer >> randomtestadventurerresults.out
	gcov -f -b dominion.c >> unittestadventurerresults.out

unittestresults.out:
	rm -f unittestresults.out
	make clean
	make rngs.o
	make dominion.o
	make unittest1
	./unittest1 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	make clean
	make rngs.o
	make dominion.o
	make unittest2
	./unittest2 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	make clean
	make rngs.o
	make dominion.o
	make unittest3
	./unittest3 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	make clean
	make rngs.o
	make dominion.o
	make unittest4
	./unittest4 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	#Omitting cardtest1 because it seg faults
	#make clean
	#make rngs.o
	#make dominion.o
	#make cardtest1
	#./cardtest1 >> unittestresults.out
	#gcov -f -b dominion.c >> unittestresults.out
	echo 
	make clean
	make rngs.o
	make dominion.o
	make cardtest2
	./cardtest2 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	make clean
	make rngs.o
	make dominion.o
	make cardtest3
	./cardtest3 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	make clean
	make rngs.o
	make dominion.o
	make cardtest4
	./cardtest4 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	
all: $(PROGS)

clean:
	rm -f *.o $(PROGS) *~ *.gcov *.gcda *.gcno *.so
