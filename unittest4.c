/*Tyler Hadley
 * hadleyt@onid.oregonstate.edu
 * CS362-400
 * assignment3 - unittest4 - drawCard()
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
	int i, p, d; //counter generic, players, decksize
	int g;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
		smithy, village, baron, great_hall};
	struct gameState state;
	struct gameState previous;
	int testDeck[MAX_DECK];
	int testHand[MAX_HAND] = {adventurer, copper, silver, province, smithy};//arbitrary starting hand
	int testDiscard[MAX_DECK] = {copper, copper, estate, baron, village};
	int testDeckSize = 25;
	int testHandSize = 5;
	int testDiscardSize = 5;
	int random;

	printf("Testing drawCard():\n");
	for(p = 0; p < MAX_PLAYERS; p++){
		for(d = 0; d< testDeckSize; d++){
#if(NOISY_TEST == 1)
			printf("\nPlayer: %d, Deck Size: %d\n", p, d);
#endif
			memset(&state, 23, sizeof(struct gameState)); //fill state with EOL
			g = initializeGame(MAX_PLAYERS, k, 1000, &state); //initialize game
			for(i = 0; i < d; i++){
				random = (int)(Random() * 10);
				testDeck[i] = k[random];//randomly select from available kingdom cards 
			}
			state.deckCount[p] = d;
			memcpy(state.deck[p], testDeck, sizeof(int) * MAX_DECK);//test deck
			memcpy(state.hand[p], testHand, sizeof(int) * MAX_HAND);//test hand
			state.handCount[p] = testHandSize;
			memcpy(state.discard[p], testDiscard, sizeof(int) * MAX_DECK);//test discard
			state.discardCount[p] = testDiscardSize;
			previous = state;
#if(NOISY_TEST == 1)
			printf("Drawing...\n");
#endif
			drawCard(p, &state); 
#if(NOISY_TEST == 1)
			if(d == 0){
				printf("Special Case: drawing on an empty deck\n");
				printf("Discard Count: %d, Expected %d\n", state.discardCount[p], 0);
				printf("Deck Size: %d, Expected %d\n", state.deckCount[p], previous.deckCount[p] + previous.discardCount[p] - 1);
			}else{	
				printf("Deck Size: %d, Expected: %d\n", state.deckCount[p], previous.deckCount[p] - 1);
				printf("Card Drawn: %d, Expected: %d\n", state.hand[p][state.handCount[p]-1], previous.deck[p][previous.deckCount[p] - 1]);
			}
			printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p] + 1);

#endif
#if(ASSERTS == 1)
			if(d == 0){
				assert(state.discardCount[p] == 0);
				assert(state.deckCount[p] == previous.deckCount[p] + previous.discardCount[p] -1);
			}else{	
				assert(state.deckCount[p] == previous.deckCount[p] -1);
				assert(state.hand[p][state.handCount[p]-1] == previous.deck[p][previous.deckCount[p] - 1]);
			}
			assert(state.handCount[p] == previous.handCount[p] + 1);
#endif
		}
	}

#if(ASSERTS == 1)
	printf("Tests passed.\n");
#endif
	

}
