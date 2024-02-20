#ifndef BLACKJACK21_OTHERSTUFF_H
#define BLACKJACK21_OTHERSTUFF_H

void printAscii() {
    printf(".------..------..------..------..------..------..------..------..------.\n");
    printf("|B.--. ||L.--. ||A.--. ||C.--. ||K.--. ||J.--. ||A.--. ||C.--. ||K.--. |.-.\n");
    printf("| :(): || :(): || :(): || :(): || :(): || :(): || :(): || :(): || :(): ((2))\n");
    printf("| ()() || (__) || ()() || (__) || (__) || ()() || (__) || ()() || ()() |'-.-.\n");
    printf("| '--'B|| '--'L|| '--'A|| '--'C|| '--'K|| '--'J|| '--'A|| '--'C|| '--'K| ((1))\n");
    printf(")`------'`------'`------'`------'`------'`------'`------'`------'`------'  '-'\n");
}

void betDeliverer(player *p, gameSettings *settings, int dealerValue) {
    for (int i = 0; i < settings->numPlay; i++) {
        if (p[i].status == 3) {
            p[i].money += p[i].bet * settings->blackjackMultiplier;
        } else if (p[i].status == 2) {
            if (dealerValue > 21) {
                p[i].money += p[i].bet * settings->winMultiplier; // Dealer overshot
            } else if (dealerValue > playerHandValue(&p[i])) {
                p[i].money -= p[i].bet;
            } else if (dealerValue < playerHandValue(&p[i])) {
                p[i].money += p[i].bet * settings->winMultiplier; // Dealer undershot
            }
        } else if (p[i].status == 1) {
            p[i].money -= p[i].bet;
        }
    }
}

#endif //BLACKJACK21_OTHERSTUFF_H
