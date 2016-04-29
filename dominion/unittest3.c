#include "dominion.h"
#include <stdio.h>

int failed = 0;

int myassert(int b, char* msg) {
	if (b == 0) {
		printf("FAILED ASSERTION: %s\n", msg);
		failed = 1;
	}
}

void checkasserts() {
	if (!failed) {
		printf("TEST SUCCESSFULLY COMPLETED.\n");
	}
}

/*Testing buyCard*/

int main() {
	struct gameState g;

	int k[10] = { smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute };

	int r = initializeGame(2, k, 5, &g);

	myassert(r == 0, "Everything correct should make this succeed");

	//no money to buy anything
	r = buyCard(0, &g);

	myassert(r == 0, "buyCard failed");

	checkasserts();

	return 0;
}