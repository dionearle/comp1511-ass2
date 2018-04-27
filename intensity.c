// intensity.c
// Assignment 2, COMP1511 18s1: Intensity
//
// This program by Dion Earle (z5205292) on 07/05/2018
//
// Version 1.0.1: Minor changes to wording of comments.
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <assert.h>

// SOME USEFUL #defines - YOU WILL NEED MORE

#define ACTION_PLAYER_NAME    0
#define ACTION_DISCARD        1
#define ACTION_PLAY_CARD      2
#define ACTION_UNIT_TESTS     3

#define N_CARDS              40
#define N_CARDS_INITIAL_HAND 10
#define N_PLAYERS             4
#define N_CARDS_DISCARDED     3

#define CARD_MIN             10
#define CARD_MAX             49


#define N_CARDS_PLAYED_MAX 3
#define N_PREV_CARDS_PLAYED_MAX 36
#define CALF_MIN 30
#define CALF_MAX 39

void print_player_name(void);
void choose_discards(void);
void choose_card_to_play(void);
void run_unit_tests(void);


// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE




// You should not need to change this main function

int main(void) {

    int which_action = 0;
    scanf("%d", &which_action);
    if (which_action == ACTION_PLAYER_NAME) {
        print_player_name();
    } else if (which_action == ACTION_DISCARD) {
        choose_discards();
    } else if (which_action == ACTION_PLAY_CARD) {
        choose_card_to_play();
    } else {
        run_unit_tests();
    }

    return 0;
}

void print_player_name(void) {
    printf("Chef");
}

void choose_discards() {

    // ADD CODE TO READ THE CARDS OF YOUR HAND INTO AN ARRAY USING SCANF

    int cardArray[N_CARDS_INITIAL_HAND] = {};

	int i = 0;
	while (i < N_CARDS_INITIAL_HAND) {
        scanf("%d", &cardArray[i]);
        i++;
	}

	// THEN ADD YOUR CODE HERE TO CHOOSE AND PRINT THE CARDS YOU WISH TO DISCARD

	int discardOne = cardArray[7];
	int discardTwo = cardArray[8];
	int discardThree = cardArray[9];

    printf("%d %d %d\n", discardOne, discardTwo, discardThree);

}



void choose_card_to_play(void) {

    int numMyCards;
    scanf("%d", &numMyCards);

    int numCardsPlayed;
    scanf("%d", &numCardsPlayed);

    int tablePos;
    scanf("%d", &tablePos);
    
    // ADD CODE TO READ THE CARDS OF YOUR HAND INTO AN ARRAY USING SCANF

    int myCardsArray[N_CARDS_INITIAL_HAND];
    
    int i = 0;
    while (i < numMyCards) {
        scanf("%d", &myCardsArray[i]);
        i++;
	}
    
    // ADD CODE TO READ THE CARDS PLAYED THIS ROUND INTO AN ARRAY USING SCANF

    int cardsPlayedArray[N_CARDS_PLAYED_MAX];
    
    int j = 0;
    while (j < numCardsPlayed) {
        scanf("%d", &cardsPlayedArray[j]);
        j++;
	}
    
    // ADD CODE TO READ THE CARDS PREVIOUSLY PLAYED IN OTHER ROUNDS INTO AN ARRAY USING SCANF

    int numPrevCardsPlayed = (N_CARDS_INITIAL_HAND - numMyCards) * N_PLAYERS;
    
    int prevCardsPlayedArray[N_PREV_CARDS_PLAYED_MAX];

    int k = 0;
    while (k < numPrevCardsPlayed) {
        scanf("%d", &prevCardsPlayedArray[k]);
        k++;
	}


    //Cards player discarded at start of game
    int cardsDiscardedArray[N_CARDS_DISCARDED];

    int a = 0;
    while (a < N_CARDS_DISCARDED) {
        scanf("%d", &cardsDiscardedArray[a]);
        a++;
    }

    //Cards player recieved at start of game
    int cardsRecievedArray[N_CARDS_DISCARDED];

    int b = 0;
    while (b < N_CARDS_DISCARDED) {
        scanf("%d", &cardsRecievedArray[b]);
        b++;
    }
    
    // THEN ADD YOUR CODE HERE TO CHOOSE AND PRINT THE CARD YOU WISH TO PLAY
    
    //0 means a calf has not yet been played, so you cannot start a round with card between 30 - 39
    int calfPlayed = 0;
    
    //check each member in previous cards array for a calf (card between 30 and 39)
    int d = 0;
    while (d < numPrevCardsPlayed) {
        if (prevCardsPlayedArray[d] >= CALF_MIN && prevCardsPlayedArray[d] <= CALF_MAX) {
            calfPlayed = 1;
        }
        d++;
	}
    
 
    //If first player, pick lowest second digit card (that is legal) 
    int cardToPlay = myCardsArray[0];
    
    if (numCardsPlayed == 0) {
        int c = 1;
        while (c < numMyCards) {
            if ((myCardsArray[c] % 10 < cardToPlay % 10)) {
                if ((myCardsArray[c] < CALF_MIN || myCardsArray[c] > CALF_MAX)
                || calfPlayed != 0) {
                    cardToPlay = myCardsArray[c];
                }
            }
            c++;
	    }
    }
    
    //If not first player, pick lowest second digit card (that is legal)
    int legalCardMin;
    int legalCardMax;
    
    if (numCardsPlayed != 0) {
        if (cardsPlayedArray[0] >= 10 && cardsPlayedArray[0] <= 19) {
            legalCardMin = 10;
            legalCardMax = 19;
        } else if (cardsPlayedArray[0] >= 20 && cardsPlayedArray[0] <= 29) {
            legalCardMin = 20;
            legalCardMax = 29;
        } else if (cardsPlayedArray[0] >= 30 && cardsPlayedArray[0] <= 39) {
            legalCardMin = 30;
            legalCardMax = 39;
        } else {
            legalCardMin = 40;
            legalCardMax = 49;
        }
        
        int e = 1;
        while (e < numMyCards) {
            if ((myCardsArray[e] >= legalCardMin) && (myCardsArray[e] <= legalCardMax)) {
                if ((cardToPlay < legalCardMin) || (cardToPlay > legalCardMax)) {
                    cardToPlay = myCardsArray[e];
                } else if ((cardToPlay >= legalCardMin && cardToPlay <= legalCardMax)
                && (myCardsArray[e] % 10 < cardToPlay % 10)) {
                    cardToPlay = myCardsArray[e];
                }
	        }
	        e++;
        }
    }
    
    printf("%d\n", cardToPlay);

}


// ADD A COMMENT HERE EXPLAINING YOUR OVERALL TESTING STRATEGY

void run_unit_tests(void) {
    // PUT YOUR UNIT TESTS HERE
}


// ADD YOUR FUNCTIONS HERE

