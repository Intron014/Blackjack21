#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "playerIneitor.h"
#include "cardIneitor.h"

int main() {
    // Init
    srand(time(NULL));
    hand h[52];
    handGenerator(h);

    // Players
    int numPlay = 0;
    while(numPlay<2 || numPlay>4) {
        printf("How many players are going to play? (2-4): ");
        scanf("%i", &numPlay);
    }
    player gaymers[numPlay];
    for(int i=0; i<numPlay; i++) {
        char name[50];
        printf("Enter the name of player %i: ", i+1);
        scanf("%s", name);
        playerGenerator(&gaymers[i], name);
    }

    // Game
    int game = 1;
    while(game) {
        for (int i = 0; i < numPlay; i++) {
            printf("Player %s's Turn\n> $%i\nEnter your bet: ", gaymers[i].name, gaymers[i].money);
            scanf("%i", &gaymers[i].bet);
        }
        for (int i = 0; i < numPlay; i++) {
            playerHandReset(&gaymers[i]);
            int isAlive = 1;
            autoFirstDeal(&gaymers[i], h);
            for (int j = 2; isAlive ; j++) {
                printf("Player %s's Turn\n", gaymers[i].name);
                printf("Your hand (%i): \n", handValue(&gaymers[i]));
                cardPrinter(gaymers[i].hand, j);
                printf("Do you want another card? (1-Yes, 0-No): ");
                scanf("%i", &isAlive);
            }
        }
    }

}

