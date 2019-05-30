// unittest2.c
// This will test the card adventurer

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main()
{
	printf("----------Testing the Refactored Adventurer Card.----------\n");
	int seed = 1000;
	int numPlayers = 2;
	int playerOne = 0;
	int playerTwo = 1;
	struct gameState copyG, actualG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	//Off of the created variables above, create a new game state and set player cards
	initializeGame(numPlayers, k, seed, &copyG);

	memcpy(&actualG, &copyG, sizeof(struct gameState));
	int returnValue = adventurerEffect(0, &actualG);

	//First assert is to verify that two cards have been added to the hand
	if(actualG.handCount[playerOne] == copyG.handCount[playerOne] + 2)
	{
		printf("SUCCESS: The cards drawn are the correct ammount.\n");
	}
	else
	{
		printf("FAILURE: The cards drawn are wrong, Expected: %d, Actual: %d.\n", copyG.handCount[playerOne] + 2, actualG.handCount[playerOne]);
	}

	//Second is to check it drew from the right pile
	if(actualG.deckCount[playerOne] == copyG.deckCount[playerOne] - 2)
	{
		printf("SUCCESS: The deck contains the correct amount of cards\n");
	}
	else
	{
		printf("FAILURE: The deck is wrong, Expected: %d, Actual: %d.\n", copyG.deckCount[playerOne] - 2, actualG.deckCount[playerOne]);
	}

	//Third is to check if the cards drawn are treasures
	int cardOne = actualG.hand[playerOne][actualG.handCount[playerOne]-2];
	int cardTwo = actualG.hand[playerOne][actualG.handCount[playerOne]-1];
	if((cardOne == copper || cardOne == silver || cardOne == gold) && (cardTwo == copper || cardTwo == silver || cardTwo == gold))
	{
		printf("SUCCESS: Cards are valid treasures.\n");
	}
	else
	{
		printf("FAILURE: One of the two cards drawn are not treasures.\n");
	}

	//fourth and fifth is to check the other player was unaffected
	assert(actualG.handCount[playerTwo] == copyG.handCount[playerTwo]);
	printf("SUCCESS: Other player's hand count is correct.\n");
	assert(actualG.deckCount[playerTwo] == copyG.deckCount[playerTwo]);
	printf("SUCCESS: Other player's deck count is correct.\n");

	//Lastly is to check it returned successfully
	assert(returnValue == 0);
	printf("SUCCESS: Return successful\n");


	/*
	memcpy(&actualG, &copyG, sizeof(struct gameState));
	int returnValue = playAdventurer(&actualG, drawnTreasure, playerOne, cardDrawn, z, temphand);

	// Then all above tests again, however this would cause an infinite loop as no treasures would be found,
	// as drawntreasure would never increase.
	*/
}