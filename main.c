#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "playerIneitor.h"
#include "dealerIneitor.h"
#include "cardIneitor.h"

int main() {
    // Init
    srand(time(NULL));
    hand h[52];
    handGenerator(h);

    // Players
    int numPlay = 0;
    int game = 0;
    while(game < 1 || game > 10) {
        printf("How many rounds are going to be played? (1-10): ");
        scanf("%i", &game);
    }
    while(numPlay<2 || numPlay>4) {
        printf("How many players are going to play? (2-4): ");
        scanf("%i", &numPlay);
    }
    player gaymers[numPlay];
    dealer gayler;
    for(int i=0; i<numPlay; i++) {
        char name[50];
        printf("Enter the name of player %i: ", i+1);
        scanf("%s", name);
        playerGenerator(&gaymers[i], name);
    }

    // Game
    while(game) {
        for (int i = 0; i < numPlay; i++) {
            printf("Player %s's Turn\n> $%i\nEnter your bet: ", gaymers[i].name, gaymers[i].money);
            scanf("%i", &gaymers[i].bet);
        }
        dealerHandReset(&gayler);
        dealerFirstDeal(&gayler, h);
        dealerCardPrinter(gayler.hand, 2);
        for (int i = 0; i < numPlay; i++) {
            playerHandReset(&gaymers[i]);
            int isAlive = 1;
            for (int j = 0; isAlive ; j++) {
                if(j<1) {
                    printf("Player %s's Turn\n", gaymers[i].name);
                    playerFirstDeal(&gaymers[i], h);
                    if(playerHandValue(&gaymers[i]) == 21) {
                        printf("Blackjack!\n");
                        gaymers[i].status = 3;
                        isAlive = 0;
                    }
                    j=1;
                } else {
                    int card;
                    int isWritten = 0;
                    do {
                        card = rand() % 52;
                        if (h[card].howmany) {
                            gaymers[i].hand[j].value = h[card].value;
                            strcpy(gaymers[i].hand[j].name, h[card].name);
                            h[card].howmany--;
                            isWritten = 1;
                        }
                    } while (!isWritten);
                }
                printf("Your hand (%i): \n", playerHandValue(&gaymers[i]));
                playerCardPrinter(gaymers[i].hand, j + 1);
                if(playerHandValue(&gaymers[i]) > 21) {
                    printf("You are busted!\n");
                    gaymers[i].status = 1;
                    isAlive = 0;
                } else{
                    printf("Do you want another card? (1-Yes, 0-No): ");
                    scanf("%i", &isAlive);
                    if(!isAlive) {
                        gaymers[i].status = 2;
                    }
                }
            }
        }
        printf("Dealer's Turn: \n");
        gayler.hand[1].isHidden = 0;
        int isAlive = 1;
        for (int j = 2; isAlive ; j++) {
            printf("(%i)\n", dealerHandValue(&gayler));
            dealerCardPrinter(gayler.hand, j);
            if(dealerHandValue(&gayler) <= 17) {
                int card;
                int isWritten = 0;
                do {
                    card = rand() % 52;
                    if (h[card].howmany) {
                        gayler.hand[j].value = h[card].value;
                        strcpy(gayler.hand[j].name, h[card].name);
                        h[card].howmany--;
                        isWritten = 1;
                    }
                } while (!isWritten);
            } else {
                isAlive = 0;
            }
        }
        // Bet delivery system
        for(int i=0; i<numPlay; i++) {
            if(gaymers[i].status == 3) {
                gaymers[i].money += gaymers[i].bet*3;
            } else if(gaymers[i].status == 2) {
                if(dealerHandValue(&gayler) > 21) {
                    gaymers[i].money += gaymers[i].bet*2;
                } else if(dealerHandValue(&gayler) > playerHandValue(&gaymers[i])) {
                    gaymers[i].money -= gaymers[i].bet;
                } else if(dealerHandValue(&gayler) < playerHandValue(&gaymers[i])) {
                    gaymers[i].money += gaymers[i].bet*2;
                }
            } else if(gaymers[i].status == 1) {
                gaymers[i].money -= gaymers[i].bet;
            }
        }
        game--;
    }
    // Results
    for(int i=0; i<numPlay; i++) {
        printf("Player %s: $%i\n", gaymers[i].name, gaymers[i].money);
    }

}

