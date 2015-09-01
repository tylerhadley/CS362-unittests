/*Tyler Hadley
 * hadleyt@onid.oregonstate.edu
 * CS362-400
 * assignment3 - cardtest1 - adventurer()
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
	int allTreasure[MAX_DECK];
	int noTreasure[MAX_DECK];
	int mixed[MAX_DECK];
	int tempHand[MAX_HAND];
	int hand[MAX_HAND] = {adventurer};
	int z = 0; //counter for temp hand
	int deckSize = 5;
	int numPlayers = 4;
	int random;
	int drawnTreasure, cardDrawn;

	//fill test decks
	for(i = 0; i < MAX_DECK; i++){
		allTreasure[i] = copper;
		noTreasure[i] = k[6];//smithy
		if(i%2 == 0)
			mixed[i] = copper;
		else
			mixed[i] = k[6];
	}

	printf("Testing adventurer():\n");
	for(p = 0; p < numPlayers; p++){
		for(d = 0; d< deckSize; d++){
#if(NOISY_TEST == 1)
			printf("\nPlayer: %d, Deck Size: %d, Hand: one adventurer\n", p, d);
#endif
			memset(&state, 23, sizeof(struct gameState)); //fill with EOL
			g = initializeGame(numPlayers, k, 1000, &state); //initialize
			drawnTreasure = 0; 
			z = 0;
			cardDrawn = 0;
			state.deckCount[p] = d;
			memcpy(state.deck[p], allTreasure, sizeof(int) * MAX_DECK);
			memcpy(state.hand[p], hand, sizeof(int) * MAX_HAND);
			state.handCount[p] = 1;
			previous = state;
#if(NOISY_TEST == 1)
			printf("\nTesting all treasure deck\n");
#endif
			zzzadventurercardplay(drawnTreasure, p, cardDrawn, tempHand, z, &state);
#if(NOISY_TEST == 1)
			if(d < 2)
				printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p] -1 + d);
			else 
				printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p] - 1 + 2);
#endif
#if(ASSERTS == 1)
			if(d < 2)
				assert(state.handCount[p] ==  previous.handCount[p] - 1 + d);
			else
				assert(state.handCount[p] == previous.handCount[p] - 1 + 2);
#endif
#if(NOISY_TEST == 1)
			if(d < 2)
				printf("Deck + Discard + Played: %d, Expected: %d\n", state.discardCount[p] + state.playedCardCount + state.deckCount[p], previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 - d );	
			else
				printf("Deck + Discard + Played: %d, Expected: %d\n", state.discardCount[p] + state.playedCardCount + state.deckCount[p], previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] - 1 );	
#endif	
#if(ASSERTS == 1)
			if(d < 2)
				assert(state.discardCount[p] + state.playedCardCount + state.deckCount[p] == previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 - d);	
			else
				assert(state.discardCount[p] + state.playedCardCount + state.deckCount[p] == previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] - 1);	
#endif	
#if(NOISY_TEST == 1)
			if(d < 2)
				printf("Expected cards in hand: only %d, %d, %d, or no cards\n", copper, silver, gold);
			else
				printf("Expected cards in hand: only %d, %d, or %d\n", copper, silver, gold);
			printf("Actual cards:\n");
			for(i = 0; i < state.handCount[p]; i++)
				printf("%d ", state.hand[p][i]);
			printf("\n");
#endif
#if(ASSERTS == 1)
			for(i = 0; i < state.handCount[p]; i++)
				assert(state.hand[p][i] == copper || state.hand[p][i] == silver || state.hand[p][i] == gold);
#endif

#if(NOISY_TEST == 1)
			printf("\nTesting no treasure deck\n");
#endif
			state = previous;
			cardDrawn = 0;
			z = 0;
			drawnTreasure = 0;
			memcpy(state.deck[p], noTreasure, sizeof(int) * MAX_DECK);
			previous = state;
			zzzadventurercardplay(drawnTreasure, p, cardDrawn, tempHand, z, &state);
 
#if(NOISY_TEST == 1)
			printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p] - 1);
#endif
#if(ASSERTS == 1)
			assert(state.handCount[p] ==  previous.handCount[p] - 1);
#endif
#if(NOISY_TEST == 1)
			printf("Deck + Discard + Played: %d, Expected: %d\n", state.discardCount[p] + state.playedCardCount + state.deckCount[p], previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 );	
#endif	
#if(ASSERTS == 1)
			assert(state.discardCount[p] + state.playedCardCount + state.deckCount[p] == previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 );	
#endif	
#if(NOISY_TEST == 1)
			printf("Expected cards in hand: none\n");
			printf("Actual cards:\n");
			for(i = 0; i < state.handCount[p]; i++)
				printf("%d ", state.hand[p][i]);
			printf("\n");
#endif
#if(ASSERTS == 1)
			for(i = 0; i < state.handCount[p]; i++)
				assert(state.hand[p][i] == copper || state.hand[p][i] == silver || state.hand[p][i] == gold);
#endif

#if(NOISY_TEST == 1)
			printf("\nTesting mixed treasure deck\n");
#endif

			state = previous;
			drawnTreasure = 0;
			cardDrawn = 0;
			z = 0;
			memcpy(state.deck[p], mixed, sizeof(int) * MAX_DECK);
			previous = state;
			zzzadventurercardplay(drawnTreasure, p, cardDrawn, tempHand, z, &state);
		 
#if(NOISY_TEST == 1)
			printf("Expected cards in hand: only %d, %d, %d, or no cards\n", copper, silver, gold);
			printf("Actual cards:\n");
			for(i = 0; i < state.handCount[p]; i++)
				printf("%d ", state.hand[p][i]);
			printf("\n");
#endif
#if(ASSERTS == 1)
			for(i = 0; i < state.handCount[p]; i++)
				assert(state.hand[p][i] == copper || state.hand[p][i] == silver || state.hand[p][i] == gold);
#endif
		}
	}

#if(ASSERTS == 1)
	printf("Tests passed.\n");
#endif
}
