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
                        gaymers[i].bet *= 3;
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
                    gaymers[i].bet = 0;
                    isAlive = 0;
                } else{
                    printf("Do you want another card? (1-Yes, 0-No): ");
                    scanf("%i", &isAlive);
                }
            }
        }
        game--;
        // Bet payment handler here


    }

}

