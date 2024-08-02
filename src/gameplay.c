#include "gameplay.h"
#include "rendering.h"
#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>

int isPlayable(Card card, Card topCard, Suit currentSuit) {
    return (card.rank == topCard.rank || card.suit == currentSuit || card.rank == EIGHT);
}
void playCard(CardPile *hand, int index, CardPile *discardPile, Card *topCard, Suit *currentSuit) {
    Card selectedCard = hand->cards[index];
    addCardToPile(discardPile, selectedCard);
    removeCardFromPile(hand, index);
    *topCard = selectedCard;

    if (selectedCard.rank == EIGHT) {
        *currentSuit = ChooseNewSuit();
    } else {
        *currentSuit = selectedCard.suit;
    }
}

// Välj ny färg för ett kort
/*void chooseNewSuit(Card *card) {
    int suitChoice;
    printf("Choose a new suit (1-Hearts, 2-Diamonds, 3-Clubs, 4-Spades): ");
    scanf("%d", &suitChoice);
    if (suitChoice >= 1 && suitChoice <= 4) {
        card->suit = suitChoice - 1;
    } else {
        printf("Invalid choice, keeping the same suit.\n");
    }
}*/

// Kontrollera om ett kort är spelbart
/*int isPlayable(Card card, Card topCard) {
    printf("Checking if card rank %d of suit %d is playable on top card rank %d of suit %d\n", card.rank, card.suit, topCard.rank, topCard.suit);
    return (card.rank == topCard.rank || card.suit == topCard.suit || card.rank == EIGHT);
}*/
/*void playCard(CardPile *hand, int choice, CardPile *discardPile, Card *topCard) {
    Card selectedCard = hand->cards[choice - 1];
    printf("You played: ");
    printCard(selectedCard);
    printf("\n");

    // Lägg kortet i kasthögen
    addCardToPile(discardPile, selectedCard);
    removeCardFromPile(hand, choice - 1);

    // Hantera specialkort
    if (selectedCard.rank == EIGHT) {
       // chooseNewSuit(&selectedCard);  // Låt spelaren välja ny färg
    }

    *topCard = selectedCard;
}*/


// Kontrollera om det finns flera kort av samma rang i handen
int hasMultipleOfSameRank(CardPile *hand, Rank rank) {
    int count = 0;
    for (int i = 0; i < hand->size; i++) {
        if (hand->cards[i].rank == rank) {
            count++;
        }
    }
    return count > 1;
}
void playMultipleCardsOfSameRank(CardPile *hand, Rank rank, CardPile *discardPile, Card selectedCard, int initialChoice, Card *topCard) {
    addCardToPile(discardPile, selectedCard);
    removeCardFromPile(hand, initialChoice - 1);

    bool promptActive = true;
    Vector2 buttonPosition = { 300, 200 }; // Knappens position
    Vector2 buttonSize = { 200, 50 }; // Knappens storlek

    while (promptActive) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("You have multiple cards of the same rank.", 200, 100, 20, DARKGRAY);
        DrawText("Click on the cards you want to play.", 200, 130, 20, DARKGRAY);
        DrawText("Press the button below to finish choosing.", 200, 160, 20, DARKGRAY);

        // Rita knappen
        DrawRectangle(buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y, LIGHTGRAY);
        DrawRectangleLines(buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y, DARKGRAY);
        DrawText("Finish Choosing", buttonPosition.x + 10, buttonPosition.y + 10, 20, DARKGRAY);

        // Rita korten
        for (int i = 0; i < hand->size; i++) {
            if (hand->cards[i].rank == rank) {
                RenderCardSuit(hand->cards[i], 100 + i * 70, 200);
            }
        }

        EndDrawing();

        // Kontrollera om knappen har klickats
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            if (mousePosition.x > buttonPosition.x && mousePosition.x < buttonPosition.x + buttonSize.x &&
                mousePosition.y > buttonPosition.y && mousePosition.y < buttonPosition.y + buttonSize.y) {
                promptActive = false;
            }
        }

        // Kontrollera om en av korten har klickats
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            for (int i = 0; i < hand->size; i++) {
                if (hand->cards[i].rank == rank) {
                    if (mousePosition.x > 100 + i * 70 && mousePosition.x < 160 + i * 70 &&
                        mousePosition.y > 200 && mousePosition.y < 290) {
                        Card cardToPlay = hand->cards[i];
                        addCardToPile(discardPile, cardToPlay);
                        removeCardFromPile(hand, i);
                        if (hand->size == 0) {
                            promptActive = false; // Stoppa om alla kort har spelats
                            break;
                        }
                    }
                }
            }
        }
    }

    if (discardPile->size > 0) {
        *topCard = discardPile->cards[discardPile->size - 1];
    }
}


// Hitta index för ett kort i handen
int findCardIndex(CardPile *hand, Card card) {
    for (int i = 0; i < hand->size; i++) {
        if (hand->cards[i].rank == card.rank && hand->cards[i].suit == card.suit) {
            return i;
        }
    }
    return -1; // Kortet finns inte i handen
}
void getDisplayRank(Rank rank, char *displayRank) {
    const char *rankStr = rankToString(rank);
    if (strcmp(rankStr, "Jack") == 0 || strcmp(rankStr, "Queen") == 0 || strcmp(rankStr, "King") == 0 || strcmp(rankStr, "Ace") == 0) {
        displayRank[0] = rankStr[0];
        displayRank[1] = '\0';
    } else {
        strcpy(displayRank, rankStr);
    }
}
