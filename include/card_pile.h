#ifndef CARD_PILE_H
#define CARD_PILE_H

#include "card.h"
#include "deck.h"

// Deklarationer för funktioner som hanterar kortsamlingar
void addCardToPile(CardPile *pile, Card card);
void printCardPile(CardPile *pile);

void removeCardFromPile(CardPile *pile, int index);


#endif // CARD_PILE_H
