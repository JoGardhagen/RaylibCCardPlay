#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "card.h"
#include "gameplay.h"
#include <string.h>
#include <raylib.h>
//#include "ai.h"

// Funktion för att skriva ut spelarens hand
/*void printHand(CardPile *hand) {
    for (int i = 0; i < hand->size; i++) {
        printf("Card %d: ", i + 1);
        printCard(hand->cards[i]);
        printf("\n");
    }
}*/

// Huvudprogrammet
/*int main() {
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
        
        
    }

    

    printf("Congratulations! You have played all your cards.\n");

    return 0;
}*/


// Funktion för att rita ett kort på skärmen
void RenderCard(Card card, int posX, int posY);
Suit ChooseNewSuit(void);

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
        addCardToPile(&aiHand, drawCard(&deck));
    }

    // Dra ett startkort till bordet från kortleken
    addCardToPile(&discardPile, drawCard(&deck));
    Card topCard = discardPile.cards[discardPile.size - 1];

    // Initiera Raylib och skapa ett fönster
    InitWindow(800, 600, "Card Game");

    // Huvudspel loopen
    while (!WindowShouldClose()) {
        // Börja rita
        BeginDrawing();

        // Rensa skärmen med en bakgrundsfärg
        ClearBackground(RAYWHITE);

        // Rita spelarens hand
        for (int i = 0; i < hand.size; i++) {
            RenderCard(hand.cards[i], 100 + i * 70, 400);
        }

        // Rita översta kortet i kasseringshögen
        DrawText("Top card: \u2665", 350, 100, 20, DARKGRAY);
        RenderCard(topCard, 400, 200);

        // Hantera användarinmatning
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            for (int i = 0; i < hand.size; i++) {
                if (mousePosition.x > 100 + i * 70 && mousePosition.x < 160 + i * 70 &&
                    mousePosition.y > 400 && mousePosition.y < 490) {
                    Card selectedCard = hand.cards[i];

                    if (isPlayable(selectedCard, topCard)) {
                        if (selectedCard.rank == EIGHT) {
                            Suit newSuit = ChooseNewSuit();
                            selectedCard.suit = newSuit;
                        }
                        if (hasMultipleOfSameRank(&hand, selectedCard.rank)) {
                            playMultipleCardsOfSameRank(&hand, selectedCard.rank, &discardPile, selectedCard, i + 1, &topCard);
                        } else {
                            playCard(&hand, i + 1, &discardPile, &topCard);
                        }
                    } else {
                        printf("Invalid card choice.\n");
                    }
                }
            }
        }

        // Avsluta rita
        EndDrawing();
    }

    // Stäng Raylib och rensa resurser
    CloseWindow();

    printf("Congratulations! You have played all your cards.\n");

    return 0;
}

void RenderCard(Card card, int posX, int posY) {
    // Kortets dimensioner
    int cardWidth = 60;
    int cardHeight = 90;

    // Rita kortets bakgrund
    DrawRectangle(posX, posY, cardWidth, cardHeight, WHITE);

    // Rita kortets ram
    DrawRectangleLines(posX, posY, cardWidth, cardHeight, BLACK);

    // Rita rank och färg text
    char rankStr[3];
    const char *suitStr = suitToString(card.suit);

    if (card.rank >= TWO && card.rank <= TEN) {
        snprintf(rankStr, sizeof(rankStr), "%d", card.rank + 2);
    } else {
        rankStr[0] = rankToString(card.rank)[0];
        rankStr[1] = '\0';
    }

    DrawText(rankStr, posX + 5, posY + 5, 20, BLACK);
    DrawText(suitStr, posX + 5, posY + 30, 20, BLACK);
}
Suit ChooseNewSuit(void) {
    // Funktion för att välja en ny färg när en 8:a spelas
    Suit newSuit = HEARTS;  // Default värde

    while (true) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Choose a new suit:", 300, 200, 20, DARKGRAY);
        DrawText("1. Hearts", 300, 250, 20, DARKGRAY);
        DrawText("2. Diamonds", 300, 280, 20, DARKGRAY);
        DrawText("3. Clubs", 300, 310, 20, DARKGRAY);
        DrawText("4. Spades", 300, 340, 20, DARKGRAY);

        EndDrawing();

        if (IsKeyPressed(KEY_ONE)) { newSuit = HEARTS; break; }
        if (IsKeyPressed(KEY_TWO)) { newSuit = DIAMONDS; break; }
        if (IsKeyPressed(KEY_THREE)) { newSuit = CLUBS; break; }
        if (IsKeyPressed(KEY_FOUR)) { newSuit = SPADES; break; }
    }

    return newSuit;
}