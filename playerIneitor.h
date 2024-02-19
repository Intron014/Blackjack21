#ifndef BLACKJACK21_PLAYERINEITOR_H
#define BLACKJACK21_PLAYERINEITOR_H

typedef struct {
    int value;
    char name[9];
    int howmany;
} playerHand;

typedef struct {
    char name[50];
    int money;
    int bet;
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
#endif //BLACKJACK21_PLAYERINEITOR_H
