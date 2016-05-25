#include "rngs.h"
#include "dominion.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//helper shuffle from http://stackoverflow.com/questions/6127503/shuffle-array-in-c
int shuffleCards(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
    return *array;
}

int main(int argc, char *argv[]){
    struct gameState G;
    
    SelectStream(1);
    PutSeed(atoi(argv[0]));
    
    if (argc < 2){
        printf("Input should match {exec randSeed}\n");
        return 0;
    }
    
    int randSeed = atoi(argv[0]);
    srand(randSeed);
    
    int allCards[20] = {adventurer, council_room, feast, gardens, mine, 
    remodel, smithy, village, baron, great_hall, minion, steward, tribute, 
    ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    
    //shuffle the cards
    shuffleCards(allCards, 20);
    int i;
    int k[10];
    //build user deck from shuffled cards
    for(i = 0; i < 10; i++){
        k[i] = allCards[i];
    }
    
    printf("Testing dominion....\n");
    
    int numPlayers = rand() % MAX_PLAYERS + 2; //numPlayers must be at least 2
    initializeGame(numPlayers, k, randSeed, &G);
    
    int money = 0;
    int smithyPos = -1;
    int adventurerPos = -1;

    int numSmithies = 0;
    int numAdventurers = 0;
    
    while (!isGameOver(&G)) {
        money = 0;
        smithyPos = -1;
        adventurerPos = -1;
        for (i = 0; i < numHandCards(&G); i++) {
            if (handCard(i, &G) == copper)
                money++;
            else if (handCard(i, &G) == silver)
                money += 2;
            else if (handCard(i, &G) == gold)
                money += 3;
            else if (handCard(i, &G) == smithy)
                smithyPos = i;
            else if (handCard(i, &G) == adventurer)
        adventurerPos = i;
        }

        if (whoseTurn(&G == 0)) {
            if (smithyPos != -1) {
                printf("0: smithy played from position %d\n", smithyPos); 
                playCard(smithyPos, -1, -1, -1, &G); 
                printf("smithy played.\n");
                money = 0;
                i=0;
                while(i<numHandCards(&G)){
                    if (handCard(i, &G) == copper){
                        playCard(i, -1, -1, -1, &G);
                        money++;
                    }
                        else if (handCard(i, &G) == silver){
                            playCard(i, -1, -1, -1, &G);
                            money += 2;
                        }
                            else if (handCard(i, &G) == gold){
                                playCard(i, -1, -1, -1, &G);
                                money += 3;
                            }
                                i++;
                }
            }

            if (money >= 8) {
                printf("0: bought province\n"); 
                buyCard(province, &G);
            }
            else if (money >= 6) {
                printf("0: bought gold\n"); 
                buyCard(gold, &G);
            }
            else if ((money >= 4) && (numSmithies < 2)) {
                printf("0: bought smithy\n"); 
                buyCard(smithy, &G);
                numSmithies++;
            }
            else if (money >= 3) {
                printf("0: bought silver\n"); 
                buyCard(silver, &G);
            }

        printf("0: end turn\n");
        endTurn(&G);
        }
        
        else {
            if (adventurerPos != -1) {
                printf("1: adventurer played from position %d\n", adventurerPos);
                playCard(adventurerPos, -1, -1, -1, &G); 
                money = 0;
                i=0;
                while(i<numHandCards(&G)){
                    if (handCard(i, &G) == copper){
                        playCard(i, -1, -1, -1, &G);
                        money++;         
                    }
                    else if (handCard(i, &G) == silver){
                        playCard(i, -1, -1, -1, &G);
                        money += 2;
                    }
                    else if (handCard(i, &G) == gold){
                        playCard(i, -1, -1, -1, &G);
                        money += 3;
                    }
                    i++;
                }
            }

        if (money >= 8) {
            printf("1: bought province\n");
            buyCard(province, &G);
        }
        else if ((money >= 6) && (numAdventurers < 2)) {
            printf("1: bought adventurer\n");
            buyCard(adventurer, &G);
            numAdventurers++;
        }
        else if (money >= 6){
            printf("1: bought gold\n");
            buyCard(gold, &G);
        }
        else if (money >= 3){
            printf("1: bought silver\n");
            buyCard(silver, &G);
        }
        printf("1: endTurn\n");
      
        endTurn(&G);      
        }

    printf ("Player 0: %d\nPlayer 1: %d\n", scoreFor(0, &G), scoreFor(1, &G));
    
    return 0;
    }
}