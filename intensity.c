// intensity.c
// Assignment 2, COMP1511 18s1: Intensity
//
// This program by Dion Earle (z5205292) on 07/05/2018
//
// Version 1.0.1: Minor changes to wording of comments.
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <assert.h>

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
#define BUFFALO 47

void print_player_name(void);
void choose_discards(void);
void choose_card_to_play(void);
void run_unit_tests(void);


// Function prototypes

void myCardsRange(int array[N_CARDS_INITIAL_HAND], int cards, int *range10, 
int *range20, int *range30, int *range40);

void compareDiscard(int i, int j, int array1[N_CARDS_INITIAL_HAND], 
int array2[N_CARDS_DISCARDED], int *chosen, 
int *range10, int *range20, int *range40);

void checkPrevRound(int numPlayed, int playedArray[N_PREV_CARDS_PLAYED_MAX], 
int *calfPlayed, int *buffaloPlayed);

int checkPenalty(int numPlayed, int playedArray[N_CARDS_PLAYED_MAX]);

void comparePlay(int i, int cardArray[N_CARDS_INITIAL_HAND], 
int *cardToPlay, int *range10, int *range20, int *range30, int *range40);

void checkLegalRange(int cardsArray[N_CARDS_PLAYED_MAX], 
int *minValue, int *maxValue);


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

    // Reading cards of my hand into an array
    int cardArray[N_CARDS_INITIAL_HAND] = {};

	int i = 0;
	while (i < N_CARDS_INITIAL_HAND) {
        scanf("%d", &cardArray[i]);
        i++;
	}

	
    // Determining how many cards I have in each range
	int range10 = 0;
	int range20 = 0;
	int range30 = 0;
	int range40 = 0;

	myCardsRange(cardArray, N_CARDS_INITIAL_HAND, &range10, &range20, &range30, &range40);

	
    // Going through my cards and choosing the three most suitable cards
    int discardArray[N_CARDS_DISCARDED] = {0};
    int checkUsedArray[N_CARDS_INITIAL_HAND] = {0};
    int chosen = 0;
    
    int d = 0;
    while (d < N_CARDS_DISCARDED) {
        int a = 0;
        while (discardArray[d] == 0) {
            if (checkUsedArray[a] == 0) {
                discardArray[d] = cardArray[a];
            }
            a++;
        }
        int j = 0;
        while (j < N_CARDS_INITIAL_HAND) {
            if (cardArray[j] > BUFFALO && checkUsedArray[j] == 0) {
                discardArray[d] = cardArray[j];
                chosen = j;
            } else if (cardArray[j] % 10 > discardArray[d] % 10
            && (cardArray[j] < CALF_MIN || cardArray[j] > CALF_MAX)
            && checkUsedArray[j] == 0) {
                discardArray[d] = cardArray[j];
                chosen = j; 
            } else if (cardArray[j] % 10 == discardArray[d] % 10
            && (cardArray[j] < CALF_MIN || cardArray[j] > CALF_MAX)
            && checkUsedArray[j] == 0) {
                compareDiscard(j, d, cardArray, discardArray, 
                &chosen, &range10, &range20, &range40);
            }
            j++;
        }
        checkUsedArray[chosen] = 1;
        d++;
    }
    
    printf("%d %d %d\n", discardArray[0], discardArray[1], discardArray[2]);
}


void choose_card_to_play(void) {

    int numMyCards;
    scanf("%d", &numMyCards);

    int numCardsPlayed;
    scanf("%d", &numCardsPlayed);

    int tablePos;
    scanf("%d", &tablePos);

    
    // Reading cards of my hand into an array 

    int myCardsArray[N_CARDS_INITIAL_HAND];
    
    int i = 0;
    while (i < numMyCards) {
        scanf("%d", &myCardsArray[i]);
        i++;
	}

    
    // Reading cards played this round into an array

    int cardsPlayedArray[N_CARDS_PLAYED_MAX];
    
    int j = 0;
    while (j < numCardsPlayed) {
        scanf("%d", &cardsPlayedArray[j]);
        j++;
	}

    
    // Reading cards played in previous rounds into an array

    int numPrevCardsPlayed = (N_CARDS_INITIAL_HAND - numMyCards) * N_PLAYERS;
    int numRoundsPlayed = numPrevCardsPlayed / N_PLAYERS;
    
    int prevCardsPlayedArray[N_PREV_CARDS_PLAYED_MAX];

    int k = 0;
    while (k < numPrevCardsPlayed) {
        scanf("%d", &prevCardsPlayedArray[k]);
        k++;
	}


    // Reading cards player discarded at start of game into array
    int cardsDiscardedArray[N_CARDS_DISCARDED];

    int a = 0;
    while (a < N_CARDS_DISCARDED) {
        scanf("%d", &cardsDiscardedArray[a]);
        a++;
    }


    // Reading cards player recieved at start of game into array
    int cardsRecievedArray[N_CARDS_DISCARDED];

    int b = 0;
    while (b < N_CARDS_DISCARDED) {
        scanf("%d", &cardsRecievedArray[b]);
        b++;
    }


    // Checking each member in previous cards array for a calf or buffalo
    int calfPlayed = 0;
    int buffaloPlayed = 0;
    
    checkPrevRound(numPrevCardsPlayed, prevCardsPlayedArray, 
    &calfPlayed, &buffaloPlayed);

	
	// Determining how many cards I have in each range
	int range10 = 0;
	int range20 = 0;
	int range30 = 0;
	int range40 = 0;

	myCardsRange(myCardsArray, numMyCards, &range10, &range20, &range30, &range40);

    // Checking if any penalty points have been played this round
    int penaltyPlayed = checkPenalty(numCardsPlayed, cardsPlayedArray);


    // Depending on player position, choose a suitable card to play
    int legalCardMin;
    int legalCardMax;
    int cardToPlay = myCardsArray[0];
    
    // If first player, there are two options.
    // For first five rounds, play the 48 or 49 if the buffalo has been played
    // in previous rounds. Then, choose the card with the highest second digit,
    // given it is not a calf or above 47. If there are two cards with equal
    // second digits (such as a 18 and 28), then the card which I have more of
    // that range should be used.
    // In the final five rounds, a similar strategy is used yet the lowest 
    //second digit card should be used.
    
    if (numCardsPlayed == 0) {
        int c = 1;
        while (c < numMyCards) {  
            if (numRoundsPlayed < 5) { 
                if (myCardsArray[c] > BUFFALO && buffaloPlayed == 1) {
                    cardToPlay = myCardsArray[c];
                } else if ((myCardsArray[c] % 10 > cardToPlay % 10)
                && (myCardsArray[c] < CALF_MIN || myCardsArray[c] > CALF_MAX)
                && myCardsArray[c] != BUFFALO && myCardsArray[c] != 48
                && myCardsArray[c] != 49) {
                    cardToPlay = myCardsArray[c];
                } else if ((myCardsArray[c] % 10 == cardToPlay % 10)
                && (myCardsArray[c] < CALF_MIN || myCardsArray[c] > CALF_MAX)
                && myCardsArray[c] != BUFFALO && myCardsArray[c] != 48
                && myCardsArray[c] != 49) {
                    comparePlay(c, myCardsArray, &cardToPlay, 
                    &range10, &range20, &range30, &range40);
                }
            } else {
                if ((myCardsArray[c] % 10 < cardToPlay % 10)
                && (myCardsArray[c] < CALF_MIN || myCardsArray[c] > CALF_MAX)
                && myCardsArray[c] != BUFFALO && myCardsArray[c] != 48
                && myCardsArray[c] != 49) {
                    cardToPlay = myCardsArray[c];
                } else if ((myCardsArray[c] % 10 == cardToPlay % 10)
                && (myCardsArray[c] < CALF_MIN || myCardsArray[c] > CALF_MAX)
                && myCardsArray[c] != BUFFALO && myCardsArray[c] != 48
                && myCardsArray[c] != 49) {
                    comparePlay(c, myCardsArray, &cardToPlay, 
                    &range10, &range20, &range30, &range40);
                }
            }
            c++;
	    }

	// If second or third player, we first want to find the legal card range.
	// Then, for the first five rounds, given that a penalty has not yet been played
	// and we won't play a calf or buffalo, play the highest second digit card.
	// Otherwise, play the card with the lowest second digit.
	
    } else if (numCardsPlayed == 1 || numCardsPlayed == 2) {
        checkLegalRange(cardsPlayedArray, &legalCardMin, &legalCardMax);
        
        int o = 1;
        while (o < numMyCards) { 
            if (numRoundsPlayed < 5 && penaltyPlayed == 0 
            && legalCardMin != 30 && legalCardMin != 40) {
                if ((myCardsArray[o] >= legalCardMin) 
                && (myCardsArray[o] <= legalCardMax)) {
                    if ((cardToPlay < legalCardMin) 
                    || (cardToPlay > legalCardMax)) {
                        cardToPlay = myCardsArray[o];
                    } else if ((cardToPlay >= legalCardMin 
                    && cardToPlay <= legalCardMax)
                    && (myCardsArray[o] % 10 > cardToPlay % 10)) {
                        cardToPlay = myCardsArray[o];
                    } else if (myCardsArray[o] % 10 == cardToPlay % 10) {
                        comparePlay(o, myCardsArray, &cardToPlay, 
                        &range10, &range20, &range30, &range40);
                    }
	            } 
	        } else {
                if ((myCardsArray[o] >= legalCardMin) 
                && (myCardsArray[o] <= legalCardMax)) {
                    if ((cardToPlay < legalCardMin) 
                    || (cardToPlay > legalCardMax)) {
                        cardToPlay = myCardsArray[o];
                    } else if ((cardToPlay >= legalCardMin 
                    && cardToPlay <= legalCardMax)
                    && (myCardsArray[o] % 10 < cardToPlay % 10)) {
                        cardToPlay = myCardsArray[o];
                    } else if (myCardsArray[o] % 10 == cardToPlay % 10) {
                        comparePlay(o, myCardsArray, &cardToPlay, 
                        &range10, &range20, &range30, &range40);
                    }
	            }
	        }
	        o++;
        }

    // For the final player, we again want to check the legal card range.
    // Then, if nobody else played a penalty card, just play my highest second
    // digit card. If a penalty has been played, play the lowest second digit.

    } else {
        checkLegalRange(cardsPlayedArray, &legalCardMin, &legalCardMax);
        
        int t = 1;
        while (t < numMyCards) {
            if (penaltyPlayed == 0) {
                if ((myCardsArray[t] >= legalCardMin) 
                && (myCardsArray[t] <= legalCardMax)) {
                    if ((cardToPlay < legalCardMin) 
                    || (cardToPlay > legalCardMax)) {
                        cardToPlay = myCardsArray[t];
                    } else if ((cardToPlay >= legalCardMin 
                    && cardToPlay <= legalCardMax)
                    && (myCardsArray[t] % 10 > cardToPlay % 10)) {
                        cardToPlay = myCardsArray[t];
                    } else if (myCardsArray[t] % 10 == cardToPlay % 10) {
                        comparePlay(t, myCardsArray, &cardToPlay, 
                        &range10, &range20, &range30, &range40);
                    }
	            }
	        } else {
                if ((myCardsArray[t] >= legalCardMin) 
                && (myCardsArray[t] <= legalCardMax)) {
                    if ((cardToPlay < legalCardMin) 
                    || (cardToPlay > legalCardMax)) {
                        cardToPlay = myCardsArray[t];
                    } else if ((cardToPlay >= legalCardMin 
                    && cardToPlay <= legalCardMax)
                    && (myCardsArray[t] % 10 < cardToPlay % 10)) {
                        cardToPlay = myCardsArray[t];
                    } else if (myCardsArray[t] % 10 == cardToPlay % 10) {
                        comparePlay(t, myCardsArray, &cardToPlay, 
                        &range10, &range20, &range30, &range40);
                    }
	            }
	        }
	        t++;
        }
    }

    //Check that if the card you are going to play is not in the legal range,
    //then first play cards above buffalo, then play calfs (if legal),
    //then just highest ending digit.
    if (numCardsPlayed != 0 
    && (cardToPlay < legalCardMin || cardToPlay > legalCardMax)) {
        int m = 0;
        while (m < numMyCards) {
            if (myCardsArray[m] > BUFFALO) {
                cardToPlay = myCardsArray[m];
            } else if ((myCardsArray[m] > CALF_MIN 
            && myCardsArray[m] < CALF_MAX) && calfPlayed == 1) {
                cardToPlay = myCardsArray[m];
            } else if (myCardsArray[m] % 10 > cardToPlay % 10) {
                cardToPlay = myCardsArray[m];
            } else if (myCardsArray[m] % 10 == cardToPlay % 10) {
                comparePlay(m, myCardsArray, &cardToPlay, 
                &range10, &range20, &range30, &range40);
            }
            m++;
        } 
    }
    
    printf("%d\n", cardToPlay);

}


// ADD A COMMENT HERE EXPLAINING YOUR OVERALL TESTING STRATEGY

void run_unit_tests(void) {
    //Insert assert statements here
}


// ADD YOUR FUNCTIONS HERE

void myCardsRange(int array[N_CARDS_INITIAL_HAND], int cards, int *range10, 
int *range20, int *range30, int *range40) {

    int i = 0;
	while (i < cards) {
        if (array[i] <= 19) {
            (*range10)++;
        } else if (array[i] >= 20 && array[i] <= 29) {
            (*range20)++;
        } else if (array[i] >= 30 && array[i] <= 39) {
            (*range30)++;
        } else {
            (*range40)++;
        }
        i++;
	}
}



void compareDiscard(int i, int j, int array1[N_CARDS_INITIAL_HAND], 
int array2[N_CARDS_DISCARDED], int *chosen, 
int *range10, int *range20, int *range40) {

    int card1range = 0;
    int card2range = 0;
    
    if (array1[i] <= 19) {
        card1range = *range10; 
    } else if (array1[i] >= 20 && array1[i] <= 29) {
        card1range = *range20;
    } else {
        card1range = *range40;
    }
    
    if (array2[j] <= 19) {
        card2range = *range10; 
    } else if (array2[j] >= 20 && array2[j] <= 29) {
        card2range = *range20;
    } else {
        card2range = *range40;
    }
    
    if (card1range > card2range) {
        array2[j] = array1[i];
        *chosen = i;
    }
}


void checkPrevRound(int numPlayed, int playedArray[N_PREV_CARDS_PLAYED_MAX], 
int *calfPlayed, int *buffaloPlayed){

    int i = 0;
    while (i < numPlayed) {
        if (playedArray[i] >= CALF_MIN && playedArray[i] <= CALF_MAX) {
            *calfPlayed = 1;
        } else if (playedArray[i] == BUFFALO) {
            *buffaloPlayed = 1;
        }
        i++;
	}
}


int checkPenalty(int numPlayed, int playedArray[N_CARDS_PLAYED_MAX]) {

    int penaltyPlayed = 0;
    
	int i = 0;
	while (i < numPlayed) {
        if ((playedArray[i] > CALF_MIN && playedArray[i] < CALF_MAX) 
        || playedArray[i] == BUFFALO) {
            penaltyPlayed = 1;
        }
        i++;
	}
    
	return penaltyPlayed;
}


void comparePlay(int i, int cardArray[N_CARDS_INITIAL_HAND], int *cardToPlay, 
int *range10, int *range20, int *range30, int *range40) {

    int card1range = 0;
    int card2range = 0;

    if (cardArray[i] <= 19) {
        card1range = *range10; 
    } else if (cardArray[i] >= 20 && cardArray[i] <= 29) {
        card1range = *range20;
    } else if (cardArray[i] >= 30 && cardArray[i] <= 39)  {
        card1range = *range30;
    } else {
        card1range = *range40;
    }
    
    if (*cardToPlay <= 19) {
        card2range = *range10; 
    } else if (*cardToPlay >= 20 && *cardToPlay <= 29) {
        card2range = *range20;
    } else if (*cardToPlay >= 30 && *cardToPlay <= 39) {
        card2range = *range30;
    } else {
        card2range = *range40;
    }

    if (card1range > card2range) {
        *cardToPlay = cardArray[i];
    }
}

void checkLegalRange(int cardsArray[N_CARDS_PLAYED_MAX], 
int *minValue, int *maxValue) {

    if (cardsArray[0] <= 19) {
        *minValue = 10;
        *maxValue = 19;
    } else if (cardsArray[0] >= 20 && cardsArray[0] <= 29) {
        *minValue = 20;
        *maxValue = 29;
    } else if (cardsArray[0] >= 30 && cardsArray[0] <= 39) {
        *minValue = 30;
        *maxValue = 39;
    } else {
        *minValue = 40;
        *maxValue = 49;
    }
}
