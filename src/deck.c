#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "card_pile.h"




CardPile deck = { .cards = {0}, .size = 0, .capacity = DECK_SIZE };
CardPile discardPile = { .cards = {0}, .size = 0, .capacity = DECK_SIZE };

void initializeDeck(CardPile *deck) {
    int index = 0;
    for (int suit = HEARTS; suit <= SPADES; suit++) {
        for (int rank = TWO; rank <= ACE; rank++) {
            deck->cards[index].rank = rank;
            deck->cards[index].suit = suit;
            index++;
        }
    }
    deck->size = DECK_SIZE;
    deck->capacity = DECK_SIZE;
}
void shuffleDeck(CardPile *deck) {
    srand(time(NULL)); // Initiera slumpgeneratorn
    for (int i = deck->size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
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