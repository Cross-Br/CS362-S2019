#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
/*
*   Random test for smithyEffect function
*   Function definition: 
*   int smithyEffect(int handPos, int currentPlayer, struct gameState *state)
*
*/

int testSmithyEffect(int handPos, int p, struct gameState *post);

int main () {
    int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

    struct gameState G;
    
    int n, i, p, result;
    SelectStream(2);
    PutSeed(4);
    printf ("*****RUNNING smithyEffect() RANDOM TESTS...*****\n");

    for (n = 0; n < 2000; n++) {
        printf ("---Test %d:\n", n+1);
        // Generate random game state
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }

        // Random player
        p = floor(Random() * 4);

        // Random deck
        G.deckCount[p] = floor(Random() * MAX_DECK);
        for(i = 0; i < G.deckCount[p]; i++){
            int randCard = (rand() % (26 - 0 + 1)) + 0; 
            G.deck[p][i] = randCard;
        }

        // Random discard
        G.discardCount[p] = floor(Random() * MAX_DECK);
        for(i = 0; i < G.discardCount[p]; i++){
            int randCard = (rand() % (26 - 0 + 1)) + 0; 
            G.discard[p][i] = randCard;
        }

        // Random hand
        G.handCount[p] = floor(Random() * MAX_HAND);
        for(i = 0; i < G.handCount[p]; i++){
            int randCard = (rand() % (26 - 0 + 1)) + 0; 
            G.hand[p][i] = randCard;
        }

        // Random played card count
        G.playedCardCount = floor(Random() * MAX_HAND);
        for(i = 0; i < G.playedCardCount; i++){
            int randCard = (rand() % (26 - 0 + 1)) + 0; 
            G.playedCards[i] = randCard;
        }

        // Random smithy supply
        G.supplyCount[smithy] = (rand() % (50 - 1 + 1)) + 1;

        // Gain card we are testing
        result = gainCard(smithy, &G, 2, p);
        assert(result == 0);
        
        // Run test function
        int handPos = G.handCount[p]-1;
        testSmithyEffect(handPos, p, &G);

        printf("\n");
    }

    return 0;
}


int testSmithyEffect(int handPos, int p, struct gameState *post){
    printf("TESTING SMITHY EFFECT...\n");
    printf ("PLAYER NUMBER: %d\n", p);

    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    int result;

    int initial_handsize = pre.handCount[p];
    printf("Initial Handsize: %d\n", initial_handsize);

    result = smithyEffect(handPos, p, post);
    assert(result == 0);

    int final_handsize = post->handCount[p];
    printf("Final Handsize: %d\n", final_handsize);

    //assert(final_handsize == (initial_handsize+2));
    if (final_handsize == (initial_handsize+2)) {
        printf("PASSED.\n");
    } else {
        printf("FAILED.\n");
    }

    return 0;
}
