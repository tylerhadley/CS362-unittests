/*Tyler Hadley
 * hadleyt@onid.oregonstate.edu
 * CS362-400
 * assignment3 - cardtest4 - great_hall()
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define ASSERTS 1 //set to 0 to disable asserts
#define NOISY_TEST 1 //set to 0 to remove printfs from output

int main(){
	//counter generic, players, decksize, handsize, position of smithy
	int i, p, d, s, m;
	int g;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
		smithy, village, baron, great_hall};
	struct gameState state;
	struct gameState previous;
	int allTreasure[MAX_DECK];
	int noTreasure[MAX_DECK];
	int mixed[MAX_DECK];
	int testHandSize = 5;
	int deckSize = 5;
	int numPlayers = 2;
	int random;

	//fill test decks
	for(i = 0; i < MAX_DECK; i++){
		allTreasure[i] = copper;
		noTreasure[i] = k[6];//smithy
		if(i%2 == 0)
			mixed[i] = copper;
		else
			mixed[i] = k[6];
	}

	printf("Testing great_hall():\n");
	for(p = 0; p < numPlayers; p++){
		for(d = 0; d< deckSize; d++){
		for(s = 0; s < testHandSize; s++){
		for(m = 0; m < testHandSize; m++){
#if(NOISY_TEST == 1)
			printf("\nPlayer: %d, Deck Size: %d, Hand: %d, Great Hall Position: %d\n", p, d, s, m);
#endif
			memset(&state, 23, sizeof(struct gameState)); //fill with EOL
			g = initializeGame(numPlayers, k, 1000, &state); //initialize
			state.deckCount[p] = d;
			memcpy(state.deck[p], mixed, sizeof(int) * MAX_DECK);
			memcpy(state.hand[p], allTreasure, sizeof(int) * MAX_HAND);
			state.handCount[p] = s;
			state.hand[p][m] = great_hall; //test different locations of great hall card
			previous = state;
#if(NOISY_TEST == 1)
			printf("\nTesting mixed treasure and action deck\n");
#endif
			zzzgreathallcardplay(p, m, &state);
#if(NOISY_TEST == 1)
			if(d < 1)
				printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p] -1 + d);
			else 
				printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p]);
#endif
#if(ASSERTS == 1)
			if(d < 1)
				assert(state.handCount[p] ==  previous.handCount[p] - 1 + d);
			else
				assert(state.handCount[p] == previous.handCount[p]);
#endif
#if(NOISY_TEST == 1)
			if(d < 1)
				printf("Deck + Discard + Played: %d, Expected: %d\n", state.discardCount[p] + state.playedCardCount + state.deckCount[p], previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1);	
			else
				printf("Deck + Discard + Played: %d, Expected: %d\n", state.discardCount[p] + state.playedCardCount + state.deckCount[p], previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] );	
#endif	
#if(ASSERTS == 1)
			if(d < 1)
				assert(state.discardCount[p] + state.playedCardCount + state.deckCount[p] == previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1);	
			else
				assert(state.discardCount[p] + state.playedCardCount + state.deckCount[p] == previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p]);	
#endif	
#if(NOISY_TEST == 1)
			printf("Actions: %d, Expected: %d\n", state.numActions, previous.numActions +1 );
#endif
#if(ASSERTS == 1)
			assert(state.numActions == previous.numActions + 1);
#endif

		}}}
	}

#if(ASSERTS == 1)
	printf("Tests passed.\n");
#endif
}
