#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "card.h"
#include "gameplay.h"
#include "rendering.h"
#include <string.h>
#include <raylib.h>
#include <unistd.h>
#include <limits.h>

//Texture2D heart, diamond, club, spade;


//Suit ChooseNewSuit(void);
void printCardDetails(CardPile *pile) {
    for (int i = 0; i < pile->size; i++) {
        printf("Card %d: Rank %d, Suit %d\n", i, pile->cards[i].rank, pile->cards[i].suit);
    }
}

int main() {
    // Initiera och blanda kortleken
    
    initializeDeck(&deck);
    shuffleDeck(&deck);
    printCardDetails(&deck);

    CardPile hand = { .cards = {0}, .size = 0, .capacity = DECK_SIZE };

    //CardPile aiHand = { .cards = {0}, .size = 0, .capacity = DECK_SIZE };

    // Dra initiala kort till spelarens hand
    for (int i = 0; i < 5; i++) {
        addCardToPile(&hand, drawCard(&deck));
        //addCardToPile(&aiHand, drawCard(&deck));
    }
    for(int i = 0;i<hand.size;i++){
            printf("Card %d: Rank %d, Suit %d\n",i+1,hand.cards[i].rank,hand.cards[i].suit);
    }


    // Dra ett startkort till bordet från kortleken
    addCardToPile(&discardPile, drawCard(&deck));
    Card topCard = discardPile.cards[discardPile.size - 1];

    // Initiera Raylib och skapa ett fönster
    InitWindow(800, 600, "Card Game");

    LoadTextures();

    Rectangle drawButton = { 300, 500, 200, 50 };

    // Huvudspel loopen
    while (!WindowShouldClose()) {
        // Börja rita
        BeginDrawing();
        
        // Rensa skärmen med en bakgrundsfärg
        ClearBackground(RAYWHITE);

        RenderPlayerHand(&hand);

        // Rita översta kortet i kasseringshögen
        DrawText("Top card:", 350, 100, 20, DARKGRAY);
        //RenderCard(topCard, 400, 200);
        RenderCardSuit(topCard,400,200);

        if (Button(drawButton, "Draw Card", LIGHTGRAY)) {
            if (deck.size > 0) {
                addCardToPile(&hand, drawCard(&deck));
                addCardToPile(&hand, drawCard(&deck));
                addCardToPile(&hand, drawCard(&deck));
            }
        }

        // Hantera användarinmatning
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            for (int i = 0; i < hand.size; i++) {
                if (mousePosition.x > 100 + i * 70 && mousePosition.x < 160 + i * 70 &&
                    mousePosition.y > 400 && mousePosition.y < 490) {
                    Card selectedCard = hand.cards[i];
                    printf("Card rank : %d  suit : %d \n", selectedCard.rank,selectedCard.suit);

                    if (isPlayable(selectedCard, topCard)) {
                        if (selectedCard.rank == EIGHT) {
                            Suit newSuit = ChooseNewSuit();
                            selectedCard.suit = newSuit;
                        }
                        if (hasMultipleOfSameRank(&hand, selectedCard.rank)) {
                           // Lägg till en knapp för att hantera kort av samma rang
                            Vector2 playMultipleButtonPosition = { 300, 500 };
                            Vector2 playMultipleButtonSize = { 200, 50 };
                            DrawRectangle(playMultipleButtonPosition.x, playMultipleButtonPosition.y, playMultipleButtonSize.x, playMultipleButtonSize.y, LIGHTGRAY);
                            DrawRectangleLines(playMultipleButtonPosition.x, playMultipleButtonPosition.y, playMultipleButtonSize.x, playMultipleButtonSize.y, DARKGRAY);
                            DrawText("Play Multiple Cards", playMultipleButtonPosition.x + 10, playMultipleButtonPosition.y + 10, 20, DARKGRAY);

                            if (mousePosition.x > playMultipleButtonPosition.x && mousePosition.x < playMultipleButtonPosition.x + playMultipleButtonSize.x &&
                                mousePosition.y > playMultipleButtonPosition.y && mousePosition.y < playMultipleButtonPosition.y + playMultipleButtonSize.y) {
                                playMultipleCardsOfSameRank(&hand, selectedCard.rank, &discardPile, selectedCard, i + 1, &topCard);
                            }
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
        UnloadTextures();


    // Stäng Raylib och rensa resurser

   
    CloseWindow();

    printf("Congratulations! You have played all your cards.\n");

    return 0;
}
