// cardtest4.c
// This will test the card great hall

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	printf("----------Testing the Great Hall Card Through cardEffect.----------\n");
	//Initialize the variables
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handPos = 0;
	int bonus = 0;

	int seed = 1000;
	int numPlayers = 2;
	int playerOne = 0;
	int playerTwo = 1;
	struct gameState copyG, actualG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	//Off of the created variables above, create a new game state and set player cards
	initializeGame(numPlayers, k, seed, &copyG);

	memcpy(&actualG, &copyG, sizeof(struct gameState));
	int returnValue = cardEffect(great_hall, choice1, choice2, choice3, &actualG, handPos, &bonus);

	//First assert is to check the hand size the same as one card was drawn, one discarded
	if(actualG.handCount[playerOne] == copyG.handCount[playerOne])
	{
		printf("SUCCESS: The cards in the hand are the correct ammount.\n");
	}
	else
	{
		printf("FAILURE: The cards in the hand are wrong, Expected: %d, Actual: %d.\n", copyG.handCount[playerOne], actualG.handCount[playerOne]);
	}

	//Second is to check the number of actions increased
	if(actualG.numActions == copyG.numActions + 1)
	{
		printf("SUCCESS: Actions was increased by one.\n");
	}
	else
	{
		printf("FAILURE: Actions is not correct, Expected: %d, Actual: %d.\n", copyG.numActions + 1, actualG.numActions);
	}

	//Third and fourth is to check the other player was unaffected
	assert(actualG.handCount[playerTwo] == copyG.handCount[playerTwo]);
	printf("SUCCESS: Other player's hand count is correct.\n");
	assert(actualG.deckCount[playerTwo] == copyG.deckCount[playerTwo]);
	printf("SUCCESS: Other player's deck count is correct.\n");

	//Lastly is to check it returned successfully
	assert(returnValue == 0);
	printf("SUCCESS: Return successful\n");
}