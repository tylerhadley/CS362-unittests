/*Tyler Hadley
 * hadleyt@onid.oregonstate.edu
 * CS362-400
 * assignment3 - unittest1 - test updateCoins()
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define ASSERTS 1 //set to 0 to disable asserts
#define NOISY_TEST 1 //set to 0 to remove printfs from output

int main(){
	int i, p, h, b; //counters generic, player, hand, bonus
	int g; 
	int maxBonus = 10;
	int handSize = 7;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel,
		smithy, village, baron, great_hall};
	struct gameState state;
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];

	printf("Creating control hands\n");
	for(i = 0; i < handSize; i++){
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;
	}
	

	printf("Testing updateCoins():\n");
	for(p = 0; p < MAX_PLAYERS; p++){
		for(h = 1; h <= handSize; h++){
			for(b = 1; b <= maxBonus; b++){
#if(NOISY_TEST == 1)
				printf("Player: %d, Treasures in Hand: %d, Bonus: %d.\n", p, h, b);
#endif
				memset(&state, 23, sizeof(struct gameState)); //fill state with EOL
				g = initializeGame(MAX_PLAYERS, k, 1000, &state); //initialize game
				state.handCount[p] = h; //set cards in hand
				memcpy(state.hand[p], coppers, sizeof(int) * MAX_HAND);//all coppers
				updateCoins(p, &state, b);
#if(NOISY_TEST == 1)
				printf("Coins = %d, Expected: %d\n", state.coins, h * 1 + b);
#endif
#if(ASSERTS == 1)
				assert(state.coins == h * 1 + b);
#endif
                                memcpy(state.hand[p], silvers, sizeof(int) * MAX_HAND);//all coppers
                                updateCoins(p, &state, b);
#if(NOISY_TEST == 1)
                                printf("Coins = %d, Expected: %d\n", state.coins, h * 2 + b);
#endif
#if(ASSERTS == 1)
				assert(state.coins == h * 2 + b);
#endif
                                memcpy(state.hand[p], golds, sizeof(int) * MAX_HAND);//all coppers
                                updateCoins(p, &state, b);
#if(NOISY_TEST == 1)
                                printf("Coins = %d, Expected: %d\n", state.coins, h * 3 + b);
#endif
#if(ASSERTS == 1)
				assert(state.coins == h * 3 + b);
#endif

			}
		}
	}
	printf("Tests passed.\n");

	

}
