#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "card_pile.h"

CardPile deck;
CardPile discardPile;


void initializeDeck(CardPile *deck) {
    deck->size = 0;
    deck->capacity = DECK_SIZE;
    for (int suit = 0; suit < NUM_SUITS; suit++) {
        for (int rank = 0; rank < NUM_RANKS; rank++) {
            if (rank != EIGHT) {
                deck->cards[deck->size].rank = rank;
                deck->cards[deck->size].suit = suit;
                deck->size++;
            }
        }
    }
    // Lägg till åttorna
    for (int suit = 0; suit < NUM_SUITS; suit++) {
        deck->cards[deck->size].rank = EIGHT;
        deck->cards[deck->size].suit = suit;
        deck->size++;
    }
}

void shuffleDeck(CardPile *deck) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < deck->size; i++) {
        int j = rand() % deck->size;
        Card temp = deck->cards[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}
// Dra ett kort från kortleken
Card drawCard(CardPile *deck) {
    if (deck->size > 0) {
        return deck->cards[--deck->size];
    } else {
        Card emptyCard = { .rank = 0, .suit = 0 }; // Returnera ett tomt kort om kortleken är tom
        return emptyCard;
    }
}
// Dra flera kort till handen
void drawMultipleCardsToHand(CardPile *hand, int count, CardPile *deck, CardPile *discardPile) {
    for (int i = 0; i < count; i++) {
        if (deck->size == 0) {
            // Flytta kort från discardPile till deck
            for (int j = 0; j < discardPile->size; j++) {
                addCardToPile(deck, discardPile->cards[j]);
            }
            discardPile->size = 0;
            shuffleDeck(deck);
        }
        addCardToPile(hand, drawCard(deck));
    }
}