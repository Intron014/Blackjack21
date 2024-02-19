#include <stdio.h>
#include <string.h>
#include "cardIneitor.h"
#include "playerIneitor.h"

int main() {
    // Init
    hand h[52];
    handGenerator(h);

    // Players
    int numPlay = 0;
    while(numPlay<2 || numPlay>4) {
        printf("How many players are going to play? (2-4)\r");
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
            printf("Player %s, enter your bet: ", gaymers[i].name);
            scanf("%i", &gaymers[i].bet);
        }
        // for (int i = 0; i < numPlay; i++) {
        //     playerHandReset(&gaymers[i]);
        //     for (int j = 0; j < 2; j++) {
        //         int card = rand() % 52
        //         gaymers[i].hand[j].value = h[card].value;
        //         strcpy(gaymers[i].hand[j].name, h[card].name);
        //         h[card].howmany--;
        //     }
        // }
    }

}

