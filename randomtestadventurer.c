/*
Tyler Hadley
CS362
assignment 4 - randomtestadventurer.c
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <time.h>

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
	SelectStream(2);
	PutSeed(time(NULL));

	int num_tests = 5000;
	struct gameState state, previous;
#if(NOISY_TEST == 1)
	printf("Testing Adventurer against %d random gamestates\n", num_tests);
#endif
	for(int test = 0; test < num_tests; test++){
		for(int p = 0; p < MAX_PLAYERS; p++){
			//start adventurer specific counters
			int drawnTreasure = 0;
			int cardDrawn = 0;
			int tempHand[MAX_HAND];
			int z = 0;
			//end adventurer specific counters
			int treasures_in_deck = 0;
			int treasures_in_hand = 0;
			int prev;
			random_gamestate(&state);
			int adventurer_pos = (int)(Random()*state.handCount[p]);	//random adventurer position
			state.hand[p][adventurer_pos] = adventurer;
			int d = state.deckCount[p];
			previous = state;
		
			//count treasures in deck
			for(int i = 0; i < state.deckCount[p]; i++)
				if(state.deck[p][i] == copper || state.deck[p][i] == silver || state.deck[p][i] == gold)
					treasures_in_deck+=1;
			
#if(NOISY_TEST == 1)
			printf("Randomly generated deck contains %d treasure cards\n", treasures_in_deck);
#endif
			
			//count treasures in hand
			for(int i = 0; i < state.handCount[p]; i++)
				if(state.hand[p][i] == copper || state.hand[p][i] == silver || state.hand[p][i] == gold)
					treasures_in_hand+=1;
#if(NOISY_TEST == 1)
			printf("Randomly generated hand contains %d treasure cards\n", treasures_in_hand);
#endif
			zzzadventurercardplay(drawnTreasure, p, cardDrawn, tempHand, z, &state);


			//check hand size
			if(d<2){
				if(treasures_in_deck >= d){
#if(NOISY_TEST == 1)
					printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p] -1 + d);
#endif
#if(ASSERTS == 1)
					assert(state.handCount[p] == previous.handCount[p] - 1 + d);
#endif
				}else{
#if(NOISY_TEST == 1)
					printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p] -1 + treasures_in_deck);
#endif
#if(ASSERTS == 1)
					assert(state.handCount[p] == previous.handCount[p] - 1 + treasures_in_deck);
#endif
			}}
			else{
				if(treasures_in_deck < 2){
#if(NOISY_TEST == 1)
					printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p] -1 + treasures_in_deck);
#endif
#if(ASSERTS == 1)
					assert(state.handCount[p] == previous.handCount[p] -1 + treasures_in_deck);
#endif
				}else{
#if(NOISY_TEST == 1)
					printf("Hand Size: %d, Expected: %d\n", state.handCount[p], previous.handCount[p] +1);
#endif
#if(ASSERTS == 1)
					assert(state.handCount[p] == previous.handCount[p] +1);
#endif
			}}		

			//check deck size
			if(d<2){
				if(treasures_in_deck >= d){
#if(NOISY_TEST == 1)
					printf("Deck + Discard + Played: %d, Expected: %d\n", state.discardCount[p] + state.playedCardCount + state.deckCount[p], previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 - d );
#endif
#if(ASSERTS == 1)
					assert(state.discardCount[p] + state.playedCardCount + state.deckCount[p] == previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 - d);
#endif
				}else{
#if(NOISY_TEST == 1)
					printf("Deck + Discard + Played: %d, Expected: %d\n", state.discardCount[p] + state.playedCardCount + state.deckCount[p], previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 - treasures_in_deck );	
#endif
#if(ASSERTS == 1)
					assert(state.discardCount[p] + state.playedCardCount + state.deckCount[p] == previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 - treasures_in_deck);
#endif
			}}
			else{
				if(treasures_in_deck < 2){
#if(NOISY_TEST == 1)
					printf("Deck + Discard + Played: %d, Expected: %d\n", state.discardCount[p] + state.playedCardCount + state.deckCount[p], previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 - treasures_in_deck);	
#endif
#if(ASSERTS == 1)
					assert(state.discardCount[p] + state.playedCardCount + state.deckCount[p] == previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] + 1 - treasures_in_deck);
#endif
				}else{
#if(NOISY_TEST == 1)
					printf("Deck + Discard + Played: %d, Expected: %d\n", state.discardCount[p] + state.playedCardCount + state.deckCount[p], previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] -1);	
#endif
#if(ASSERTS == 1)
					assert(state.discardCount[p] + state.playedCardCount + state.deckCount[p] == previous.discardCount[p] + previous.playedCardCount + previous.deckCount[p] -1);
#endif
					
			}}		

			//check treasures in hand
			prev = treasures_in_hand;
			treasures_in_hand = 0;
			for(int i = 0; i < state.handCount[p]; i++)
				if(state.hand[p][i] == copper || state.hand[p][i] == silver || state.hand[p][i] == gold)
					treasures_in_hand++;
			
			if(d<2){
				if(treasures_in_deck >= d){
#if(NOISY_TEST == 1)
					printf("Treasures in Hand: %d, Expected: %d\n", treasures_in_hand, prev + d);
#endif
#if(ASSERTS == 1)
					assert(treasures_in_hand == prev + d);
#endif
				}else{
#if(NOISY_TEST == 1)
					printf("Treasures in Hand: %d, Expected: %d\n", treasures_in_hand, prev + treasures_in_deck);
#endif
#if(ASSERTS == 1)
					assert(treasures_in_hand == prev+treasures_in_deck);
#endif
			}}
			else{
				if(treasures_in_deck < 2){
#if(NOISY_TEST == 1)
					printf("Treasures in Hand: %d, Expected: %d\n", treasures_in_hand, prev + treasures_in_deck);
#endif
#if(ASSERTS == 1)
					assert(treasures_in_hand == prev+treasures_in_deck);
#endif
				}else{
#if(NOISY_TEST == 1)
					printf("Treasures in Hand: %d, Expected: %d\n", treasures_in_hand, prev + 2);
#endif
#if(ASSERTS == 1)
					assert(treasures_in_hand == prev + 2);
#endif
			}}		
			
		}//end players loop
	}//end tests loop

#if(NOISY_TEST == 1)
	printf("Finished testing adventurer on %d random gamestates\n", num_tests);
#endif
#if(ASSERTS == 1)
	printf("Tests passed.\n");
#endif
}//end main
