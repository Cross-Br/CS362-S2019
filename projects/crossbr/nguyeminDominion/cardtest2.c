// cardtest2.c
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
	printf("----------Testing the Adventurer Card Through cardEffect.----------\n");
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

	printf("-----Testing shuffle during adventurer-----\n");

	int draw;
	for(draw = 0; draw < 5; draw++)
	{
		drawCard(playerOne, &copyG);
		discardCard(1, playerOne, &copyG, 0);
	}

	memcpy(&actualG, &copyG, sizeof(struct gameState));
	int returnValue = cardEffect(adventurer, choice1, choice2, choice3, &actualG, handPos, &bonus);

	//Third is to check if the cards drawn are treasures
	int cardOne = actualG.hand[playerOne][actualG.handCount[playerOne]-2];
	int cardTwo = actualG.hand[playerOne][actualG.handCount[playerOne]-1];
	if((cardOne == copper || cardOne == silver || cardOne == gold) && (cardTwo == copper || cardTwo == silver || cardTwo == gold))
	{
		printf("SUCCESS: Cards are valid treasures.\n");
	}
	else
	{
		printf("FAILURE: One of the two cards drawn are not treasures. 1: %d, 2: %d.\n", cardOne, cardTwo);
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