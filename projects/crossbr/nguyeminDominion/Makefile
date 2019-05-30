CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

alltests: dominion.c rngs.o unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c randomtestcard1.c randomtestcard2.c randomtestadventurer.c

	echo "----------UNIT TESTING RESULTS----------" > alltestresults.out

	gcc -o unittest1 dominion.c unittest1.c rngs.o $(CFLAGS)
	./unittest1 >> alltestresults.out
	gcov dominion.c -b >> alltestresults.out

	gcc -o unittest2 dominion.c unittest2.c rngs.o $(CFLAGS)
	./unittest2 >> alltestresults.out
	gcov dominion.c -b >> alltestresults.out

	gcc -o unittest3 dominion.c unittest3.c rngs.o $(CFLAGS)
	./unittest3 >> alltestresults.out
	gcov dominion.c -b >> alltestresults.out

	gcc -o unittest4 dominion.c unittest4.c rngs.o $(CFLAGS)
	./unittest4 >> alltestresults.out
	gcov dominion.c -b >> alltestresults.out

	echo "----------CARD TEST RESULTS----------" >> alltestresults.out

	gcc -o cardtest1 dominion.c cardtest1.c rngs.o $(CFLAGS)
	./cardtest1 >> alltestresults.out
	gcov dominion.c -b >> alltestresults.out

	gcc -o cardtest2 dominion.c cardtest2.c rngs.o $(CFLAGS)
	./cardtest2 >> alltestresults.out
	gcov dominion.c -b >> alltestresults.out

	gcc -o cardtest3 dominion.c cardtest3.c rngs.o $(CFLAGS)
	./cardtest3 >> alltestresults.out
	gcov dominion.c -b >> alltestresults.out

	gcc -o cardtest4 dominion.c cardtest4.c rngs.o $(CFLAGS)
	./cardtest4 >> alltestresults.out
	gcov dominion.c -b >> alltestresults.out

	echo "----------RANDOM TESTING RESULTS----------" >> alltestresults.out

	gcc -o randomtest1 dominion.c randomtestcard1.c rngs.o $(CFLAGS)
	./randomtest1 >> alltestresults.out
	gcov dominion.c -fb >> alltestresults.out

	gcc -o randomtest2 dominion.c randomtestcard2.c rngs.o $(CFLAGS)
	./randomtest2 >> alltestresults.out
	gcov dominion.c -fb >> alltestresults.out

	gcc -o randomtestadventurer dominion.c randomtestadventurer.c rngs.o $(CFLAGS)
	./randomtestadventurer >> alltestresults.out
	gcov dominion.c -fb >> alltestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer randomtestresults.out