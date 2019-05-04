// unittest3.c
// This will test the card mine

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	printf("----------Testing the Refactored Mine Card.----------\n");
	//Initialize the variables
	int choice1 = 0;
	int choice2 = 0;
	int handPos = 0;
	int j = 0;
	int i = 0;

	int seed = 1000;
	int numPlayers = 2;
	int playerOne = 0;
	struct gameState copyG, actualG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	//Off of the created variables above, create a new game state and set player cards
	initializeGame(numPlayers, k, seed, &copyG);

	//Add a copper to the hand so the location is known
	gainCard(copper, &copyG, 2, playerOne);

	//Upgrade to a silver from copper
	choice1 = copper;
	choice2 = silver;

	printf("-----Testing Copper To Silver-----\n");

	memcpy(&actualG, &copyG, sizeof(struct gameState));
	int returnValue = playMine(choice1, choice2, &actualG, handPos, j, playerOne, i);

	//First assert is to verify that the hand size is one less due to the discard of the card
	if(actualG.handCount[playerOne] == copyG.handCount[playerOne] - 1)
	{
		printf("SUCCESS: The cards drawn are the correct ammount.\n");
	}
	else
	{
		printf("FAILURE: The cards drawn are wrong, Expected: %d, Actual: %d.\n", copyG.handCount[playerOne] - 1, actualG.handCount[playerOne]);
	}

	//Second is to check the new card is a silver, it's at zero due to discardCard
	int cardOne = actualG.hand[playerOne][0];
	if(cardOne == silver)
	{
		printf("SUCCESS: The new card is a silver\n");
	}
	else
	{
		printf("FAILURE: the new card is not a silver, Expected: %d, Actual: %d.\n", silver, cardOne);
	}

	//Third is to check the funciton returned correctly
	assert(returnValue == 0);
	printf("SUCCESS: Return successful\n");

		//Upgrade to a silver from copper
	choice1 = copper;
	choice2 = gold;

	printf("-----Testing Copper To Gold-----\n");

	memcpy(&actualG, &copyG, sizeof(struct gameState));
	returnValue = playMine(choice1, choice2, &actualG, handPos, j, playerOne, i);

	//First assert is to verify that the hand size is one less due to the discard of the card
	if(returnValue == -1)
	{
		printf("SUCCESS: function failed correctly\n");
	}
	else
	{
		printf("FAILURE: the funciton let the upgrade go through\n");
	}
}