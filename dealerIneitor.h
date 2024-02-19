#ifndef BLACKJACK21_DEALERINEITOR_H
#define BLACKJACK21_DEALERINEITOR_H

typedef struct {
    int value;
    char name[9];
    int isHidden;
} dealerHand;

typedef struct {
    dealerHand hand[10];
} dealer;

void dealerHandReset(dealer *p) {
    for(int i = 0; i < 10; i++) {
        p->hand[i].value = 0;
        strcpy(p->hand[i].name, "");
    }
}

void dealerFirstDeal(dealer *p, hand *h) {
    int card;
    int isWritten = 0;
    do {
        card = rand() % 52;
        if (h[card].howmany) {
            p->hand[0].value = h[card].value;
            strcpy(p->hand[0].name, h[card].name);
            p->hand[0].isHidden = 0;
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
            p->hand[1].isHidden = 1;
            h[card].howmany--;
            isWritten = 1;
        }
    } while (!isWritten);
}

void dealerCardPrinter(dealerHand *h, int size){
    for(int i=0; i<size; i++) {
        printf(" _______ ");
    }
    printf("\n");
    for(int i=0; i<size; i++) {
        if(h[i].isHidden) {
            printf("|?      |");
        } else if(h[i].value<10) {
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
        if(h[i].isHidden) {
            printf("|   ?   |");
        } else {
            printf("|   %c   |", h[i].name[0]);
        }
    }
    printf("\n");
    for(int i=0; i<size; i++) {
        printf("|       |");
    }
    printf("\n");
    for(int i=0; i<size; i++) {
        if (h[i].isHidden){
            printf("|______?|");
        } else if(h[i].value<10) {
            printf("|______%i|", h[i].value);
        } else {
            printf("|_____%i|", h[i].value);
        }
    }
    printf("\n");
}

#endif //BLACKJACK21_DEALERINEITOR_H
