#ifndef BLACKJACK21_CARDINEITOR_H
#define BLACKJACK21_CARDINEITOR_H

typedef struct {
    int value;
    char name[9];
    int howmany;
} hand;

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


#endif //BLACKJACK21_CARDINEITOR_H
