// unittest1.c
// This will randomly test the card council room

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
	printf("----------Testing the Refactored Council Room Card W/ Random Tests----------\n");
	//Initialize the variables
	int i = 0;
	int j, k, l, m, n, o, p;
	int handPos = 0;
	int playerCount;

	//Setting up the random funciton
	SelectStream(2);
	PutSeed(3);

	//Creating the gamestates
	struct gameState baseG, actualG;

	//This is only run a couple times (20) but still covers 100% of the branches
	for(j = 0; j < 20; j++)
	{
		//Randomize the gamestate
		for(k = 0; k < sizeof(struct gameState); k++)
		{
			((char*)&baseG)[k] = floor(Random() * 256);
		}
		//Then set the playercount and hand, discard, and deck sizes manually as those will cause errors
		playerCount = floor(Random()*3)+1;
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

		//Needed for funcitons that the FUT calls
		baseG.playedCardCount = 0;

		//Gamestate is copied and the funciton is ran
		memcpy(&actualG, &baseG, sizeof(struct gameState));
		int returnValue = playCouncilRoom(&actualG, handPos, i, 0);

		//First assert is to check to make sure that the hand count has gone up 3
		if(actualG.handCount[0] == baseG.handCount[0] + 3)
		{
			printf("SUCCESS: The cards drawn are the correct ammount.\n");
		}
		else
		{
			printf("FAILURE: The cards drawn are wrong, Expected: %d, Actual: %d.\n", baseG.handCount[0] + 3, actualG.handCount[0]);
		}

		//Second is to check it drew from the right pile
		if(actualG.deckCount[0] == baseG.deckCount[0] - 4)
		{
			printf("SUCCESS: The deck contains the correct amount of cards\n");
		}
		else
		{
			printf("FAILURE: The deck is wrong, Expected: %d, Actual: %d.\n", baseG.deckCount[0] - 4, actualG.deckCount[0]);
		}

		printf("-----Testing The Other Player-----\n");

		//Third and fourth is to check the other player drew one card and lost one card from the deck
		//Start at 1 to avoid player one
		for(p = 1; p < playerCount; p++)
		{
			if(actualG.handCount[p] == baseG.handCount[p] + 1)
			{
				printf("SUCCESS: The cards drawn are the correct ammount.\n");
			}
			else
			{
				printf("FAILURE: The cards drawn for the other player are wrong, Expected: %d, Actual: %d.\n", baseG.handCount[p] + 1, actualG.handCount[p]);
			}

			if(actualG.deckCount[p] == baseG.deckCount[p] - 1)
			{
				printf("SUCCESS: The deck contains the correct amount of cards\n");
			}
			else
			{
				printf("FAILURE: The deck is wrong for the other player, Expected: %d, Actual: %d.\n", baseG.deckCount[p] - 1, actualG.deckCount[p]);
			}
		}

		//Lastly is to check it returned successfully
		assert(returnValue == 0);
		printf("SUCCESS: Return successful\n");
	}
}