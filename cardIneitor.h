#ifndef BLACKJACK21_CARDINEITOR_H
#define BLACKJACK21_CARDINEITOR_H

typedef struct {
    int value;
    char name[9];
    int howmany;
}hand;

void handGenerator(hand *h) {
    for(int i=0 ; i<52 ; i++) {
        h[i].value = i%13;
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

void cardPrinter(hand *h, int size){
    for(int i=0; i<size; i++) {
        printf(" _______ ");
    }
    printf("\n");
    for(int i=0; i<size; i++) {
        printf("|%i      |", h[i].value);
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
        printf("|______%i|", h[i].value);
    }
    printf("\n");
}

#endif //BLACKJACK21_CARDINEITOR_H
