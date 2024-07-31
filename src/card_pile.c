#include "card_pile.h"
#include <stdio.h>

// Lägg till ett kort i en kortsamling
void addCardToPile(CardPile *pile, Card card) {
    if (pile->size < pile->capacity) {
        pile->cards[pile->size++] = card;
    }
}

// Skriv ut kortsamlingen
void printCardPile(CardPile *pile) {
    for (int i = 0; i < pile->size; i++) {
        printCard(pile->cards[i]);
        printf("\n");
    }
}

// Ta bort ett kort från en kortsamling
void removeCardFromPile(CardPile *pile, int index) {
    if (index >= 0 && index < pile->size) {
        for (int i = index; i < pile->size - 1; i++) {
            pile->cards[i] = pile->cards[i + 1];
        }
        pile->size--;
    }
}


