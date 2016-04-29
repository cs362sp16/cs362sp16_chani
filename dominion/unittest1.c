#include "dominion.h"

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

/*Testing initializeGame*/

int main() {
	struct gameState g;

	int k[10] = { smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute };

	int r = initializeGame(2, k, 5, &g);

	myassert(r == 0, "Everything correct should make this succeed");

	int k2[10] = { smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute };

	r = initializeGame(2, k2, 5, &g);

	myassert(r == -1, "Duplicates should make this fail");

	checkasserts();

	return 0;
}