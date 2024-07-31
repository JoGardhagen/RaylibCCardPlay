#ifndef DECK_H
#define DECK_H

#include "card.h"

#define DECK_SIZE 52

typedef struct {
    Card cards[DECK_SIZE];
    int size;
    int capacity;
} CardPile;

extern CardPile deck;
extern CardPile discardPile;

void initializeDeck(CardPile *deck);
void shuffleDeck(CardPile *deck);
Card drawCard(CardPile *deck);
void drawMultipleCardsToHand(CardPile *hand, int count, CardPile *deck, CardPile *discardPile);


#endif // DECK_H
