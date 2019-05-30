// unittest4.c
// This will test the card council room

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	printf("----------Testing the Refactored Council Room Card.----------\n");
	//Initialize the variables
	int i = 0;
	int handPos = 0;

	int seed = 1000;
	int numPlayers = 2;
	int playerOne = 0;
	int playerTwo = 1;
	struct gameState copyG, actualG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	//Off of the created variables above, create a new game state and set player cards
	initializeGame(numPlayers, k, seed, &copyG);

	memcpy(&actualG, &copyG, sizeof(struct gameState));
	int returnValue = playCouncilRoom(&actualG, handPos, i, playerOne);

	//First assert is to check to make sure that the hand count has gone up 3
	if(actualG.handCount[playerOne] == copyG.handCount[playerOne] + 3)
	{
		printf("SUCCESS: The cards drawn are the correct ammount.\n");
	}
	else
	{
		printf("FAILURE: The cards drawn are wrong, Expected: %d, Actual: %d.\n", copyG.handCount[playerOne] + 3, actualG.handCount[playerOne]);
	}

	//Second is to check it drew from the right pile
	if(actualG.deckCount[playerOne] == copyG.deckCount[playerOne] - 4)
	{
		printf("SUCCESS: The deck contains the correct amount of cards\n");
	}
	else
	{
		printf("FAILURE: The deck is wrong, Expected: %d, Actual: %d.\n", copyG.deckCount[playerOne] - 4, actualG.deckCount[playerOne]);
	}

	printf("-----Testing The Other Player-----\n");

	//Third and fourth is to check the other player drew one card and lost one card from the deck
	if(actualG.handCount[playerTwo] == copyG.handCount[playerTwo] + 1)
	{
		printf("SUCCESS: The cards drawn are the correct ammount.\n");
	}
	else
	{
		printf("FAILURE: The cards drawn for the other player are wrong, Expected: %d, Actual: %d.\n", copyG.handCount[playerTwo] + 1, actualG.handCount[playerTwo]);
	}

	if(actualG.deckCount[playerTwo] == copyG.deckCount[playerTwo] - 1)
	{
		printf("SUCCESS: The deck contains the correct amount of cards\n");
	}
	else
	{
		printf("FAILURE: The deck is wrong for the other player, Expected: %d, Actual: %d.\n", copyG.deckCount[playerTwo] - 1, actualG.deckCount[playerTwo]);
	}

	//Lastly is to check it returned successfully
	assert(returnValue == 0);
	printf("SUCCESS: Return successful\n");
}