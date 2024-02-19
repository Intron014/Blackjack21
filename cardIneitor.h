#ifndef BLACKJACK21_CARDINEITOR_H
#define BLACKJACK21_CARDINEITOR_H

typedef struct {
    int value;
    char name[9];
    int howmany;
} hand;

int handValue(player *p) {
    int value = 0;
    for(int i=0; i<10; i++) {
        if(p->hand[i].value > 10){
            value += 10;
        } else if(p->hand[i].value == 1) {
            if(value+11 > 21)
                value += 1;
            else
                value += 11;
        } else {
            value += p->hand[i].value;
        }
    }
    return value;
}

void autoFirstDeal(player *p, hand *h) {
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

void handGenerator(hand *h) {
    for(int i=0 ; i<52 ; i++) {
        h[i].value = i%13 + 1;
        h[i].howmany = 4;
        if(i<13) {
            strcpy(h[i].name, "Hearts");
        } else if(i<26) {
            strcpy(h[i].name, "Diamonds");
        } else if(i<39) {
            strcpy(h[i].name, "Clubs");
        } else {
            strcpy(h[i].name, "Spades");
        }
    }
}

void cardPrinter(playerHand *h, int size){
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

#endif //BLACKJACK21_CARDINEITOR_H
