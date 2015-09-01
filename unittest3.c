/*Tyler Hadley
 * hadleyt@onid.oregonstate.edu
 * CS362-400
 * assignment3 - unittest3 - shuffle()
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
	int testDeckSize = 25;
	int random;

	printf("Testing shuffle():\n");
	for(p = 0; p < MAX_PLAYERS; p++){
		for(d = 0; d< testDeckSize; d++){
#if(NOISY_TEST == 1)
			printf("Player: %d, Deck Size: %d\n", p, d);
#endif
			memset(&state, 23, sizeof(struct gameState)); //fill state with EOL
			g = initializeGame(MAX_PLAYERS, k, 1000, &state); //initialize game

			for(i = 0; i < d; i++){
				random = (int)(Random() * 10);
				testDeck[i] = k[random];//randomly select from available kingdom cards 
			}
			state.deckCount[p] = d;
			memcpy(state.deck[p], testDeck, sizeof(int) * MAX_DECK);//test deck
			previous = state;
#if(NOISY_TEST == 1)
			printf("Shuffling\n");
#endif
			shuffle(p, &state); 
#if(NOISY_TEST == 1)
			printf("Previous Deck:\n");
			for(int i = 0; i < previous.deckCount[p]; i++)
				printf("%d, ", previous.deck[p][i]);
			printf("\n\nShuffled Deck:\n");
			for(int i = 0; i < state.deckCount[p]; i++)
				printf("%d, ", state.deck[p][i]);
			printf("\n\n");
#endif
#if(ASSERTS == 1)
			assert(state.deck != previous.deck);
#endif
#if(NOISY_TEST == 1)
			printf("Shuffling again to test randomness\n");	
#endif	
			state = previous;
			shuffle(p, &state); 
#if(NOISY_TEST == 1)
			printf("Previous Deck:\n");
			for(int i = 0; i < previous.deckCount[p]; i++)
				printf("%d, ", previous.deck[p][i]);
			printf("\n\nShuffled Deck:\n");
			for(int i = 0; i < state.deckCount[p]; i++)
				printf("%d, ", state.deck[p][i]);
			printf("\n\n");
#endif
#if(ASSERTS == 1)
			assert(state.deck != previous.deck);
#endif
		}
	}

#if(ASSERTS == 1)
	printf("Tests passed.\n");
#endif
	

}
