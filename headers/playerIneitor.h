#ifndef BLACKJACK21_PLAYERINEITOR_H
#define BLACKJACK21_PLAYERINEITOR_H

#include "cardIneitor.h"

typedef struct {
    int value;
    char name[9];
} playerHand;

typedef struct {
    char name[50];
    int money;
    int bet;
    int isAI;
    int status; //3: blackjack, 2: stand, 1: bust
    playerHand hand[10];
} player;

void playerGenerator(player *p, char *name) {
    strcpy(p->name, name);
    p->money = 100;
    p->bet = 0;
    for(int i = 0; i < 10; i++) {
        p->hand[i].value = 0;
        strcpy(p->hand[i].name, "");
    }
}

void playerHandReset(player *p) {
    for(int i = 0; i < 10; i++) {
        p->hand[i].value = 0;
        strcpy(p->hand[i].name, "");
    }
}

int playerHandValue(player *p) {
    int value = 0;
    int acesPos[10];
    acesposReset(acesPos);
    for(int i=0; i<10; i++) {
        if(p->hand[i].value > 10){
            value += 10;
        } else if(p->hand[i].value == 1) {
            acesPos[i] = 1;
        } else {
            value += p->hand[i].value;
        }
    }
    for(int i=0; i<10; i++) {
        if(acesPos[i]) {
            if(value+11 > 21)
                value += 1;
            else
                value += 11;
        }
    }
    return value;
}

void playerFirstDeal(player *p, hand *h) {
    int card;
    int isWritten = 0;
    do {
        card = rand() % 52;
        if (h[card].howmany) {
            p->hand[0].value = h[card].value;
            strcpy(p->hand[0].name, h[card].name);
            h[card].howmany--;
            isWritten = 1;
        }
    } while (!isWritten);
    isWritten = 0;
    do {
        card = rand() % 52;
        if (h[card].howmany) {
            p->hand[1].value = h[card].value;
            strcpy(p->hand[1].name, h[card].name);
            h[card].howmany--;
            isWritten = 1;
        }
    } while (!isWritten);
}

void playerCardPrinter(playerHand *h, int size){
    for(int i=0; i<size; i++) {
        printf(" _______ ");
    }
    printf("\n");
    for(int i=0; i<size; i++) {
        if(h[i].value<10) {
            printf("|%i      |", h[i].value);
        } else {
            printf("|%i     |", h[i].value);
        }
    }
    printf("\n");
    for(int i=0; i<size; i++) {
        printf("|       |");
    }
    printf("\n");
    for(int i=0; i<size; i++) {
        printf("|   %c   |", h[i].name[0]);
    }
    printf("\n");
    for(int i=0; i<size; i++) {
        printf("|       |");
    }
    printf("\n");
    for(int i=0; i<size; i++) {
        if(h[i].value<10) {
            printf("|______%i|", h[i].value);
        } else {
            printf("|_____%i|", h[i].value);
        }
    }
    printf("\n");
}

void resultsPrinter(player *p, int numPlayers){
    printf("\n---------Results---------\n");
    printf("| Player Name | Balance |\n");
    printf("-------------------------\n");
    for (int i = 0; i < numPlayers; i++) {
        printf("| %-11s | $%-6i |\n", p[i].name, p[i].money);
    }
    printf("-------------------------\nPress any key to continue...\n");
    fflush(stdin);
    getchar();
}
#endif //BLACKJACK21_PLAYERINEITOR_H
