#include <stdio.h>
#include <string.h>
#include "card.h"

const char *rankNames[] = {"2", "3", "4", "5", "6", "7", "9", "10", "Jack", "Queen", "King", "Ace", "8"};
const char *suitNames[] = {"♥", "♦", "♣", "♠"};

const char* rankToString(Rank rank) {
    return rankNames[rank];
}

const char* suitToString(Suit suit) {
    return suitNames[suit];
}

void printCard(Card card) {
    printf("%s of %s", rankToString(card.rank), suitToString(card.suit));
}
// Print card in ASCII
void printCardIllustrationASCII(Card card){
    const char *rank = rankToString(card.rank);
    const char *suit = suitToString(card.suit);
    char displayRank[3]; // Max två tecken plus null-terminator

    // Om ranken är klätt kort, visa endast första bokstaven
    if (strcmp(rank, "Jack") == 0 || strcmp(rank, "Queen") == 0 || strcmp(rank, "King") == 0 || strcmp(rank,"Ace")==0) {
        displayRank[0] = rank[0];
        displayRank[1] = '\0';
    } else {
        strcpy(displayRank, rank);
    }

    // Kontrollera längden på displayRank
    int rankLength = strlen(displayRank);

    printf(" \n\n _____ \n");

    // Toppen av kortet
    if (rankLength == 1) {
        printf("|%s    |\n", displayRank);       // Om ranken är 1 tecken lång (2-9)
    } else if (rankLength == 2) {
        printf("|%s   |\n", displayRank);       // Om ranken är 2 tecken lång (10)
    }

    // Mitten av kortet
    printf("|  %s  |\n", suit);

    // Botten av kortet
    if (rankLength == 1) {
        printf("|____%s|\n", displayRank);       // Om ranken är 1 tecken lång (2-9)
    } else if (rankLength == 2) {
        printf("|___%s|\n", displayRank);        // Om ranken är 2 tecken lång (10)
    }
}
