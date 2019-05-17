// unittest1.c
// This will randomly test the card smithy

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
	printf("----------Testing the Refactored Smithy Card W/ Random Tests----------\n");
	//Initialize the variables
	int i = 0;
	int j, k, l, m, n, o, p;
	int handPos = 0;
	int playerCount;

	//Setting the random seeds so the Random() function will work
	SelectStream(2);
	PutSeed(3);

	//Creating the gamestates
	struct gameState baseG, actualG;

	//Running the test 1000 times
	for(j = 0; j < 1000; j++)
	{
		//Randomizes all parts of the game state
		for(k = 0; k < sizeof(struct gameState); k++)
		{
			((char*)&baseG)[k] = floor(Random() * 256);
		}

		//Then afterwards sets the parts that need to not be random
		//first is players in the game
		playerCount = floor(Random()*3)+1;

		//Next is the deck hand and discard as they can only be a certain size and must be filled with some cards
		for(l = 0; l < playerCount; l++)
		{
			baseG.deckCount[l] = floor(Random() * MAX_DECK);
		 	baseG.handCount[l] = floor(Random() * MAX_HAND);
		 	baseG.discardCount[l] = floor(Random() * MAX_DECK);
		 	for(m = 0; m < baseG.deckCount[l]; m++)
		 	{
				baseG.deck[l][m] = floor(Random() * 26);
		 	}
		 	for(n = 0; n < baseG.handCount[l]; n++)
		 	{
		 		baseG.hand[l][n] = floor(Random() * 26);
		 	}
		 	for(o = 0; o < baseG.discardCount[l]; o++)
		 	{
		 		baseG.discard[l][o] = floor(Random() * 26);
		 	}
		}

		//These two are used in funciton s that the cards call, therefore they need to be thought about and initialized
		baseG.playedCardCount = 0;

		memcpy(&actualG, &baseG, sizeof(struct gameState));
		int returnValue = playSmithy(&actualG, handPos, i, 0);

		//First assert is to check to make sure that the hand count has gone up 2 (+3 due to smithy and -1 due to losing card)
		//assert(actualG.handCount[0] == baseG.handCount[0] + 2);
		if(actualG.handCount[0] == baseG.handCount[0] + 2)
		{
			printf("SUCCESS: The cards drawn are the correct ammount.\n");
		}
		else
		{
			printf("FAILURE: The cards drawn are wrong, Expected: %d, Actual: %d.\n", baseG.handCount[0] + 2, actualG.handCount[0]);
		}

		//Second is to check it drew from the right pile
		if(actualG.deckCount[0] <= baseG.deckCount[0] - 3)
		{
			printf("SUCCESS: The deck contains the correct amount of cards\n");
		}
		else
		{
			printf("FAILURE: The deck is wrong, Expected: %d, Actual: %d.\n", baseG.deckCount[0] - 3, actualG.deckCount[0]);
		}
		//assert(actualG.deckCount[0] - 3 == baseG.deckCount[0]);

		//Loop through the other players to make sure that their hands didnt change
		//Start at 1 to avoid player one
		for(p = 1; p < playerCount; p++)
		{
			//Third and fourth is to check the other player was unaffected
			assert(actualG.handCount[p] == baseG.handCount[p]);
			printf("SUCCESS: Other player's hand count is correct.\n");
			assert(actualG.deckCount[p] == baseG.deckCount[p]);
			printf("SUCCESS: Other player's deck count is correct.\n");
		}

		//Lastly is to check it returned successfully
		assert(returnValue == 0);
		printf("SUCCESS: Return successful\n");

	}
}