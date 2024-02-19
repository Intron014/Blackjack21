#include <stdio.h>
#include <string.h>
#include "cardIneitor.h"

int main() {
    hand h[52];
    handGenerator(h);
    for(int i=0 ; i<52 ; i++) {
        cardPrinter(h, 5);
    }
    return 0;
}

