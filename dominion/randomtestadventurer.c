#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <string.h>

#define MAX_RUNS 2000 

int numSuccess = 0, 
	numFail = 0,
	totalRuns = 0;

int adventurerCard(int currentPlayer, struct gameState *state, int drawntreasure, int cardDrawn, int temphand) {
	return 0;
}

int checkAdventurer(int z, int currentPlayer, int drawntreasure, struct gameState *state, int cardDrawn) {
	int r;

	r = adventurerCard(z, currentPlayer, drawntreasure, state, cardDrawn);
	if (r == 0) {
		return numSuccess++,totalRuns++;
	}
	else {
		return numFail++,totalRuns++;
	}
}

int main(int argc, char* argv[]) {
	int numPlayers = 2, 
		z = 0, 
		i, 
		currentPlayer, 
		drawntreasure, 
		cardDrawn = 0;

	struct gameState G;

	SelectStream(1);
	PutSeed(atoi(argv[1]));

	if (argc < 2) {
		printf("Input should match {exec randSeed}\n");
	}

	int k[10] = { smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute };

	printf("Testing adventurer card.\n");
	printf("RANDOM TESTS.\n");

	initializeGame(numPlayers, k, 1, &G);

	for (i = 0; i < MAX_RUNS; i++) {
		currentPlayer = floor(rand() % MAX_PLAYERS);
		drawntreasure = floor(rand() % 2);
		G.deckCount[0] = floor(rand() * MAX_DECK);
		checkAdventurer(z, currentPlayer, drawntreasure, &G, cardDrawn);
	}

	float percentSuccess = numSuccess / totalRuns,
		percentFail = numFail / totalRuns;

	printf("Success: %0.1f%, Fail: %0.1f%\n", percentSuccess, percentFail);
	return 0;
}