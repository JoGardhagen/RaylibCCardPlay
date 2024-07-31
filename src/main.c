#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "card.h"
#include "gameplay.h"
#include <string.h>
#include <raylib.h>
//#include "ai.h"

// Funktion för att skriva ut spelarens hand
void printHand(CardPile *hand) {
    for (int i = 0; i < hand->size; i++) {
        printf("Card %d: ", i + 1);
        printCard(hand->cards[i]);
        printf("\n");
    }
}

// Huvudprogrammet
int main() {
    // Initiera och blanda kortleken
    CardPile deck = { .cards = {0}, .size = 0, .capacity = DECK_SIZE };
    initializeDeck(&deck);
    shuffleDeck(&deck);

    // Initiera spelarens hand och kasseringshögen
    CardPile hand = { .cards = {0}, .size = 0, .capacity = DECK_SIZE };
    CardPile discardPile = { .cards = {0}, .size = 0, .capacity = DECK_SIZE };

    CardPile aiHand = { .cards = {0}, .size = 0, .capacity = DECK_SIZE };

    // Dra initiala kort till spelarens hand
    for (int i = 0; i < 5; i++) {
        addCardToPile(&hand, drawCard(&deck));
        addCardToPile(&aiHand,drawCard(&deck));
    }

    // Dra ett startkort till bordet från kortleken
    addCardToPile(&discardPile, drawCard(&deck));
    Card topCard = discardPile.cards[discardPile.size - 1];

    //int turn = 0;
    while (hand.size > 0|| aiHand.size <0) {
        //if(turn==0){
            printf("\nYour hand:\n");
        //printHand(&hand);

        printHandIllustrationASCII(&hand);

        printf("\nTop card: ");
        printCard(topCard);
        printCardIllustrationASCII(topCard);

        printf("\nChoose a card to play (1-%d, or 0 to draw 3 cards): ", hand.size);
        int choice;
        scanf("%d", &choice);

        if (choice == 0) {
            drawMultipleCardsToHand(&hand, 3, &deck, &discardPile);
        } else if (choice > 0 && choice <= hand.size) {
            Card selectedCard = hand.cards[choice - 1];

            if (isPlayable(selectedCard, topCard)) {
                if (hasMultipleOfSameRank(&hand, selectedCard.rank)) {
                    playMultipleCardsOfSameRank(&hand, selectedCard.rank, &discardPile, selectedCard, choice, &topCard);
                } else {
                    playCard(&hand, choice, &discardPile, &topCard);
                }
            } else {
                printf("Invalid card choice.\n");
            }
        } else {
            printf("Invalid choice.\n");
        }
        /*}else{
            aiPlayTurn(&aiHand,&discardPile,&topCard);
        }
        turn = 1-turn;*/
        
    }

    

    printf("Congratulations! You have played all your cards.\n");

    return 0;
}
