#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "headers/playerIneitor.h"
#include "headers/dealerIneitor.h"
#include "headers/cardIneitor.h"
#include "headers/otherStuff.h"

int main() {
    // Init
    srand(time(NULL));
    hand h[52];
    handGenerator(h);
    gameSettings settings;
    initSettings(&settings);
    system("clear");
    // Players
    do {
        do {
            printAscii();
            printf("1 - Enter the game\n2 - Access settings\n0 - Exit\n> ");
            scanf("%i", &settings.ans);
        } while (settings.ans < 0 || settings.ans > 2);
        if (settings.ans == 2) {
            printf("Blackjack Multiplier (*%i): ", settings.blackjackMultiplier);
            scanf("%i", &settings.blackjackMultiplier);
            printf("Win Multiplier (*%i): ", settings.winMultiplier);
            scanf("%i", &settings.winMultiplier);
        } else if (settings.ans == 1){
            while (settings.game < 1 || settings.game > 10) {
                printf("How many rounds are going to be played? (1-10): ");
                scanf("%i", &settings.game);
            }
            while (settings.numPlay < 1 || settings.numPlay > 4) {
                printf("How many players are going to play? (1-4): ");
                scanf("%i", &settings.numPlay);
            }
            player gaymers[settings.numPlay];
            dealer gayler;
            for (int i = 0; i < settings.numPlay; i++) {
                char name[50];
                printf("Enter the name of player %i: ", i + 1);
                scanf("%s", name);
                playerGenerator(&gaymers[i], name);

                // Game
                while (settings.game) {
                    for (int i = 0; i < settings.numPlay; i++) {
                        printf("Player %s's Turn\n", gaymers[i].name);
                        do {
                            printf("> $%i\nEnter your bet ($1 - $100): $", gaymers[i].money);
                            scanf("%i", &gaymers[i].bet);
                        } while (gaymers[i].bet <= 0 || gaymers[i].bet > 100);
                    }
                    dealerHandReset(&gayler);
                    dealerFirstDeal(&gayler, h);
                    dealerCardPrinter(gayler.hand, 2);
                    for (int i = 0; i < settings.numPlay; i++) {
                        playerHandReset(&gaymers[i]);
                        int isAlive = 1;
                        for (int j = 0; isAlive; j++) {
                            if (j < 1) {
                                printf("Player %s's Turn\n", gaymers[i].name);
                                playerFirstDeal(&gaymers[i], h);
                                if (playerHandValue(&gaymers[i]) == 21) {
                                    printf("Blackjack!\n");
                                    gaymers[i].status = 3;
                                    isAlive = 0;
                                }
                                j = 1;
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
                            if (playerHandValue(&gaymers[i]) > 21) {
                                printf("You are busted!\nPress any key to continue...\n");
                                fflush(stdin);
                                getchar();
                                gaymers[i].status = 1;
                                isAlive = 0;
                            } else {
                                if (playerHandValue(&gaymers[i]) == 21) {
                                    isAlive = 0;
                                }
                                if (!isAlive) {
                                    do {
                                        printf("Do you want another card? (0-No): ");
                                        scanf("%i", &isAlive);
                                    } while (isAlive);
                                } else {
                                    printf("Do you want another card? (1-Yes, 0-No): ");
                                    scanf("%i", &isAlive);
                                }
                                if (!isAlive && (gaymers[i].status) != 3) {
                                    gaymers[i].status = 2;
                                }
                            }
                        }
                    }
                    printf("Dealer's Turn: \n");
                    gayler.hand[1].isHidden = 0;
                    int isAlive = 1;
                    for (int j = 2; isAlive; j++) {
                        printf("(%i)\n", dealerHandValue(&gayler));
                        dealerCardPrinter(gayler.hand, j);
                        if (dealerHandValue(&gayler) <= 17) {
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
                    betDeliverer(gaymers, &settings, dealerHandValue(&gayler));
                    settings.game--;
                }
                // Results
                resultsPrinter(gaymers, settings.numPlay);
            }
        }
        system("clear");
    } while (settings.ans != 0);
}
