// unittest1.c
// This will randomly test the card adventurer

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
	int j, k, l, m, n, o, p;
	int z = 0;
	int playerCount;

	//Initializing some variables that adventurer needs that are not important
	int drawnTreasure = 0;
	int cardDrawn = 0;
	int temphand[MAX_HAND];

	//Setting up random
	SelectStream(2);
	PutSeed(3);

	//Setting up the gamestate
	struct gameState baseG, actualG;

	//This test takes a long time to run, therefore it is only run 20 times but still covers 100% of the branches
	for(j = 0; j < 50; j++)
	{
		//Randomize all of gamestate
		for(k = 0; k < sizeof(struct gameState); k++)
		{
			((char*)&baseG)[k] = floor(Random() * 256);
		}

		//Similar to smithy this is setting the variables that are needed
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

		//Here is the special variable that the funcitons call like discard
		baseG.playedCardCount = 0;

		//Here the gamestate is copied and the funciton is actually run
		memcpy(&actualG, &baseG, sizeof(struct gameState));
		int returnValue = playAdventurer(&actualG, drawnTreasure, 0, cardDrawn, z, temphand);

		//First assert is to verify that two cards have been added to the hand
		if(actualG.handCount[0] == baseG.handCount[0] + 2)
		{
			printf("SUCCESS: The cards drawn are the correct ammount.\n");
		}
		else
		{
			printf("FAILURE: The cards drawn are wrong, Expected: %d, Actual: %d.\n", baseG.handCount[0] + 2, actualG.handCount[0]);
		}

		//Second is to check it drew from the right pile
		if(actualG.deckCount[0] == baseG.deckCount[0] - 2)
		{
			printf("SUCCESS: The deck contains the correct amount of cards\n");
		}
		else
		{
			printf("FAILURE: The deck is wrong, Expected: %d, Actual: %d.\n", baseG.deckCount[0] - 2, actualG.deckCount[0]);
		}

		//Third is to check if the cards drawn are treasures
		int cardOne = actualG.hand[0][actualG.handCount[0]-2];
		int cardTwo = actualG.hand[0][actualG.handCount[0]-1];
		if((cardOne == copper || cardOne == silver || cardOne == gold) && (cardTwo == copper || cardTwo == silver || cardTwo == gold))
		{
			printf("SUCCESS: Cards are valid treasures.\n");
		}
		else
		{
			printf("FAILURE: One of the two cards drawn are not treasures.\n");
		}

		//fourth and fifth is to check the other player was unaffected
		//Start at 1 to avoid playerone
		for(p = 1; p < playerCount; p++)
		{
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