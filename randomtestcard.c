/*
Tyler Hadley
CS362
assignment 4 - randomtestcard.c - testing smithy card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

#define ASSERTS 1 //set to 0 to disable asserts
#define NOISY_TEST 1 //set to 0 to remove printfs from output

void random_gamestate(struct gameState *state){
	int players = MAX_PLAYERS;
	//printf("starting random_gamestate function\n");	
	int game;	
	int k_index = 0;
	int duplicate = 0;
	int k[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

	//printf("selecting kingdom cards\n");		
	//select 10 random, unique kingdom cards
	while(k[9] == -1){
		k[k_index] = (int)(Random()*27);//27 different kingdom cards
		//printf("k[%d] = %d\n", k_index, k[k_index]); 
		for(int i = 0; i < k_index; i++){
			if(k[i] == k[k_index]) 
				duplicate = 1;	
		}
		if(duplicate == 0)
			k_index++;
		else
			duplicate = 0;
		
	}

	game = initializeGame(players, k, 1000, state); //initialize game
	
	//printf("creating random hand\n");	
	//create random hand
	for(int p = 0; p < players; p++){
		int test_hand[MAX_HAND];
		int test_hand_size = (int)(Random() * MAX_HAND);
		for(int i = 0; i < test_hand_size; i++){
			int random = (int)(Random() * 10);
			test_hand[i] = k[random];//randomly select from k 
		}
		memcpy(state->hand[p], test_hand, sizeof(int) * MAX_HAND);
		state->handCount[p] = test_hand_size;
	}		

	//printf("creating random deck\n");	
	//create random deck
	for(int p = 0; p < players; p++){
		int test_deck[MAX_DECK];
		int test_deck_size = (int)(Random() * MAX_DECK);
		for(int i = 0; i < test_deck_size; i++){
			int random = (int)(Random() * 10);
			test_deck[i] = k[random];//randomly select from k 
		}
		memcpy(state->deck[p], test_deck, sizeof(int) * MAX_DECK);
		state->deckCount[p] = test_deck_size;
	}
	
	//printf("creating random discard\n");	
	//create random discard
	for(int p = 0; p < players; p++){
		int test_discard[MAX_DECK];
		int test_discard_size = (int)(Random() * MAX_DECK);
		for(int i = 0; i < test_discard_size; i++){
			int random = (int)(Random() * 10);
			test_discard[i] = k[random];//randomly select from k 
		}
		memcpy(state->discard[p], test_discard, sizeof(int) * MAX_DECK);
		state->discardCount[p] = test_discard_size;
	}

	//printf("creating random played cards\n");			
	//create random played cards
	int test_played[MAX_DECK];
	int test_played_size = (int)(Random() * MAX_DECK);
	for(int i = 0; i < test_played_size; i++){
		int random = (int)(Random() * 10);
		test_played[i] = k[random];//randomly select from k 
	}
	memcpy(state->playedCards, test_played, sizeof(int) * MAX_DECK);
	state->playedCardCount = test_played_size;	
}

int main(){
	int i;
	int num_tests = 2000;
	struct gameState state, previous;
#if(NOISY_TEST == 1)
	printf("Testing Smithy against %d random gamestates\n", num_tests);
#endif
	for(int test = 0; test < num_tests; test++){
		for(int p = 0; p < MAX_PLAYERS; p++){
			random_gamestate(&state);
			int smithy_pos = (int)(Random()*state.handCount[p]);	//random smithy position
			state.hand[p][smithy_pos] = smithy;
			int d = state.deckCount[p];
			previous = state;
			zzzsmithycardplay(i, p, smithy_pos, &state);
#if(NOISY_TEST == 1)
			if(d < 3)
				printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p] -1 + d);
			else 
				printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p] + 2);
#endif
#if(ASSERTS == 1)
			if(d < 3)
				assert(state.handCount[p] ==  previous.handCount[p] - 1 + d);
			else
				assert(state.handCount[p] == previous.handCount[p] + 2);
#endif
#if(NOISY_TEST == 1)
			if(d < 3)
				printf("Deck + Discard + Played: %d, Expected: %d\n", state.discardCount[p] + state.playedCardCount + state.deckCount[p], previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 - d );	
			else
				printf("Deck + Discard + Played: %d, Expected: %d\n", state.discardCount[p] + state.playedCardCount + state.deckCount[p], previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] - 2 );	
#endif	
#if(ASSERTS == 1)
			if(d < 3)
				assert(state.discardCount[p] + state.playedCardCount + state.deckCount[p] == previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 - d);	
			else
				assert(state.discardCount[p] + state.playedCardCount + state.deckCount[p] == previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] - 2 );	
#endif	
		}//end players loop
	}//end tests loop
	printf("Finished testing smithy on %d random gamestates\n", num_tests);
#if(ASSERTS == 1)
	printf("Tests passed.\n");
#endif
}//end main
