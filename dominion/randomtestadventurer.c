#include "dominion.h"
#include "dominion_helpers.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RUNS 100

int numSuccess = 0, 
	numFail = 0,
    checkRuns = 0;

int checkAdventurer(int z, int currentPlayer, struct gameState *state, int drawntreasure, int cardDrawn) {
	int r;

	r = adventurerCard(z, currentPlayer, state, drawntreasure, cardDrawn);
	if (r == 0){
        checkRuns++;
        numSuccess++;
		return;
    }
    else{
        checkRuns++;
        numFail++;
        return;
    }
}

int main(int argc, char* argv[]) {
	int numPlayers = rand() % MAX_PLAYERS + 2,   //numPlayers must be at least 2
        i;
	struct gameState G;

	SelectStream(1);
	PutSeed(atoi(argv[0]));

	if (argc < 2) {
		printf("Input should match {exec randSeed}\n");
	}

	int k[10] = { smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute };

	printf("Testing adventurer card.\n");
	printf("RANDOM TESTS.\n");

	for (i = 0; i < MAX_RUNS; i++) {
        initializeGame(numPlayers, k, atoi(argv[0]), &G);
		checkAdventurer(0, rand() % 3, &G, rand() % 3, rand() % 3);
        
        //debugging check
        /*
        if(checkRuns == 0){
            printf("ERROR LSDJFKSDJFKSDJFKSDFJ\n");
            break;
        }
        */
	}

	float percentSuccess = 100 * numSuccess / MAX_RUNS,
		percentFail = 100 * numFail / MAX_RUNS;

	printf("Success: %0.1f%, Fail: %0.1f%\n", percentSuccess, percentFail);
	return 0;
}