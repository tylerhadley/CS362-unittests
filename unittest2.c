/*Tyler Hadley
 * hadleyt@onid.oregonstate.edu
 * CS362-400
 * assignment3 - unittest2 - discardCard()
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
	int i, p, h, s; //counters generic, player, hand, position
	int handSize = 7;
	int g;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
		smithy, village, baron, great_hall};
	struct gameState state;
	struct gameState previous;
	int testHand[MAX_HAND];
	int random;

	printf("Creating control hands\n");
	for(i = 0; i < handSize; i++){
		random = (int)(Random() * 10);
		testHand[i] = k[random];//randomly select from available kingdom cards 
	}
	

	printf("Testing discardCard():\n");
	for(p = 0; p < MAX_PLAYERS; p++){
		for(h = 1; h <= handSize; h++){
			for(s = 1; s <= handSize; s++){
#if(NOISY_TEST == 1)
				printf("Player: %d, Cards in Hand: %d, Card Position in Hand: %d, Trash Flag: %d.\n", p, h,s, 0);
#endif
				memset(&state, 23, sizeof(struct gameState)); //fill state with EOL
				g = initializeGame(MAX_PLAYERS, k, 1000, &state); //initialize game
				state.handCount[p] = h; //set cards in hand
				memcpy(state.hand[p], testHand, sizeof(int) * MAX_HAND);//test hand
				previous = state;
				discardCard(s, p, &state, 0); 
#if(NOISY_TEST == 1)
				printf("Card discarded: %d, Expected: %d\n", state.playedCards[state.playedCardCount - 1], previous.hand[p][s]);
#endif
#if(ASSERTS == 1)
				assert(state.playedCards[state.playedCardCount - 1] == previous.hand[p][s]);
#endif
				
#if(NOISY_TEST == 1)
				printf("Hand size: %d, expected: %d\n", state.handCount[p], previous.handCount[p]-1); 
#endif
#if(ASSERTS == 1)
				assert(state.handCount[p] == previous.handCount[p] -1);
				for(i = 0; i < state.handCount[p]; i++)
					assert(state.hand[p][i] != -1);//make sure hand rearrangement successful
#endif

#if(NOISY_TEST == 1)
				printf("Player: %d, Cards in Hand: %d, Card Position in Hand: %d, Trash Flag: %d.\n", p, h,s, 1);
#endif
				state = previous; //reset
				discardCard(s, p, &state, 1);

#if(NOISY_TEST == 1)
				printf("Card discard size: %d, Expected: %d\n", state.playedCardCount, previous.playedCardCount);
#endif
#if(ASSERTS == 1)
				assert(state.playedCardCount == previous.playedCardCount);
#endif
				
#if(NOISY_TEST == 1)
				printf("Hand size: %d, expected: %d\n", state.handCount[p], previous.handCount[p]-1); 
#endif
#if(ASSERTS == 1)
				assert(state.handCount[p] == previous.handCount[p] -1);
				for(i = 0; i < state.handCount[p]; i++)
					assert(state.hand[p][i] != -1);//make sure hand rearrangement successful
#endif
			}
		}
	}
#if(ASSERTS == 1)
	printf("Tests passed.\n");
#endif
	

}
