// unittest1.c
// This will test the card smithy

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	printf("----------Testing the Refactored Smithy Card.----------\n");
	//Initialize the variables
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
	int returnValue = smithyEffect(handPos, 0, &actualG);

	//First assert is to check to make sure that the hand count has gone up 2 (+3 due to smithy and -1 due to losing card)
	//assert(actualG.handCount[playerOne] == copyG.handCount[playerOne] + 2);
	if(actualG.handCount[playerOne] == copyG.handCount[playerOne] + 2)
	{
		printf("SUCCESS: The cards drawn are the correct ammount.\n");
	}
	else
	{
		printf("FAILURE: The cards drawn are wrong, Expected: %d, Actual: %d.\n", copyG.handCount[playerOne] + 2, actualG.handCount[playerOne]);
	}

	//Second is to check it drew from the right pile
	if(actualG.deckCount[playerOne] == copyG.deckCount[playerOne] - 3)
	{
		printf("SUCCESS: The deck contains the correct amount of cards\n");
	}
	else
	{
		printf("FAILURE: The deck is wrong, Expected: %d, Actual: %d.\n", copyG.deckCount[playerOne] - 3, actualG.deckCount[playerOne]);
	}
	//assert(actualG.deckCount[playerOne] - 3 == copyG.deckCount[playerOne]);

	//Third and fourth is to check the other player was unaffected
	assert(actualG.handCount[playerTwo] == copyG.handCount[playerTwo]);
	printf("SUCCESS: Other player's hand count is correct.\n");
	assert(actualG.deckCount[playerTwo] == copyG.deckCount[playerTwo]);
	printf("SUCCESS: Other player's deck count is correct.\n");

	//Lastly is to check it returned successfully
	assert(returnValue == 0);
	printf("SUCCESS: Return successful\n");
}