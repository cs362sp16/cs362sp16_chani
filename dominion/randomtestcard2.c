#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <string.h>

#define MAX_RUNS 2000 

int numSuccess = 0,
numFail = 0,
totalRuns = 0;

int feastCard(struct gameState *state, int currentPlayer, int *temphand, int choice1) {
	return 0;
}

int checkfeast(struct gameState *state, int currentPlayer, int *temphand, int choice1) {
	int r;

	r = feastCard(state, currentPlayer, temphand, choice1);
	if (r == 0) {
		return numSuccess++, totalRuns++;
	}
	else {
		return numFail++, totalRuns++;
	}
}

int main(int argc, char* argv[]) {
	int numPlayers = 2,
		i,
		currentPlayer,
		temphand,
		choice1 = 0;

	struct gameState G;

	SelectStream(1);
	PutSeed(atoi(argv[1]));

	if (argc < 2) {
		printf("Input should match {exec randSeed}\n");
	}

	int k[10] = { smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute };

	printf("Testing feast card.\n");
	printf("RANDOM TESTS.\n");

	initializeGame(numPlayers, k, 1, &G);

	for (i = 0; i < MAX_RUNS; i++) {
		currentPlayer = floor(rand() % MAX_PLAYERS);
		temphand = floor(rand() % MAX_HAND);
		choice1 = floor(rand() % 2);
		checkfeast(&G, currentPlayer, temphand, choice1);
	}

	float percentSuccess = numSuccess / totalRuns,
		percentFail = numFail / totalRuns;

	printf("Success: %0.1f%, Fail: %0.1f%\n", percentSuccess, percentFail);
	return 0;
}