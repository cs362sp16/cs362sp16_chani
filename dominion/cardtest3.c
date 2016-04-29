#include "dominion.h"

int failed = 0;

void myassert(int b, char* msg) {
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

/*Testing council_room*/

int main() {
	struct gameState g;

	int j = 0;

	int k[10] = { smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute };

	int r = initializeGame(2, k, 5, &g);

	r = cardEffect(council_room, 1, 1, 1, &g, 0, &j);

	myassert(r == 0, "Council room failed");

	checkasserts();

	return 0;
}