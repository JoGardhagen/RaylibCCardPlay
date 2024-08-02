#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "card.h"
#include "card_pile.h"
#include "deck.h"

// Deklarationer för spelregler och spelrelaterade funktioner
void chooseNewSuit(Card *card);
int isPlayable(Card card, Card topCard);
int hasMultipleOfSameRank(CardPile *hand, Rank rank);
void playMultipleCardsOfSameRank(CardPile *hand, Rank rank, CardPile *discardPile, Card selectedCard, int initialChoice, Card *topCard);
int findCardIndex(CardPile *hand, Card card);
void playCard(CardPile *hand, int choice, CardPile *discardPile, Card *topCard);
void getDisplayRank(Rank rank, char *displayRank);
void printHandIllustrationASCII(CardPile *hand);

#endif // GAMEPLAY_H 