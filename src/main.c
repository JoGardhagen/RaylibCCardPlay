#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "card.h"
#include "gameplay.h"
#include <string.h>
#include <raylib.h>
#include <unistd.h>
#include <limits.h>

Texture2D heart, diamond, club, spade;
// Funktion för att rita ett kort på skärmen
void RenderCard(Card card, int posX, int posY);
Suit ChooseNewSuit(void);
bool Button(Rectangle bounds, const char *text, Color color);
bool DrawTexturedButton(Rectangle bounds, Texture2D texture);

void LoadTextures() {
    Image heartImage = LoadImage("../assets/heart.png");
    Image diamondImage = LoadImage("../assets/diamond.png");
    Image clubImage = LoadImage("../assets/club.png");
    Image spadeImage = LoadImage("../assets/spades.png");

    ImageResize(&heartImage, 30, 30);
    ImageResize(&diamondImage, 30, 30);
    ImageResize(&clubImage, 30, 30);
    ImageResize(&spadeImage, 30, 30);

    // Konvertera bilderna till texturer
    heart = LoadTextureFromImage(heartImage);
    diamond = LoadTextureFromImage(diamondImage);
    club = LoadTextureFromImage(clubImage);
    spade = LoadTextureFromImage(spadeImage);

    // Frigör bildresurser
    UnloadImage(heartImage);
    UnloadImage(diamondImage);
    UnloadImage(clubImage);
    UnloadImage(spadeImage);


}
void UnloadTextures() {
    UnloadTexture(heart);
    UnloadTexture(diamond);
    UnloadTexture(club);
    UnloadTexture(spade);
}
void DrawCardBackground(int posX, int posY, int cardWidth, int cardHeight) {
    // Rita kortets bakgrund
    DrawRectangle(posX, posY, cardWidth, cardHeight, WHITE);

    // Rita kortets kontur
    DrawRectangleLines(posX, posY, cardWidth, cardHeight, BLACK);
}
void RenderCardSuit(Card card, int x, int y){
    int cardWidth = 60;
    int cardHeight = 90;

    DrawCardBackground(x,y,cardWidth,cardHeight);
    //printf("Rendering card at position: (%d, %d)\n", x, y);
    
    Texture2D texture;
    Color textColor;
    switch(card.suit){
        case HEARTS: 
            texture = heart; 
            textColor = RED; 
            break;
        case DIAMONDS: 
            texture = diamond; 
            textColor = RED; 
            break;
        case CLUBS: 
            texture = club; 
            textColor = BLACK; 
            break;
        case SPADES: 
            texture = spade; 
            textColor = BLACK; 
            break;
        default: 
            texture = heart; 
            textColor = BLACK; 
            break; // Fallback
    }
    DrawTexture(texture, x+10,y+30,WHITE);

    const char *rankNames[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    char rankStr[3];
    if (card.rank >= TWO && card.rank <= TEN) {
        snprintf(rankStr, sizeof(rankStr), "%d", card.rank+ 2);
    } else {
        rankStr[0] = rankNames[card.rank][0];
        rankStr[1] = (card.rank == TEN) ? rankNames[card.rank][1] : '\0';
        rankStr[2] = '\0';
    }

    DrawText(rankStr, x + 10, y + 10, 20, textColor);
    


}

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

    LoadTextures();

    Rectangle drawButton = { 300, 500, 200, 50 };

    // Huvudspel loopen
    while (!WindowShouldClose()) {
        // Börja rita
        BeginDrawing();

        // Rensa skärmen med en bakgrundsfärg
        ClearBackground(RAYWHITE);

        // Rita spelarens hand
        for (int i = 0; i < hand.size; i++) {
            RenderCardSuit(hand.cards[i], 100 + i * 70, 400);
            
        }

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
                    printf("Card rank: %d\n", selectedCard.rank);

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
        UnloadTextures();


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
/*Suit ChooseNewSuit(void) {
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
}*/
bool DrawTexturedButton(Rectangle bounds, Texture2D texture) {
    Vector2 mousePosition = GetMousePosition();
    bool isPressed = false;

    // Rita knappen med textur
    DrawTextureRec(texture, (Rectangle){ 0, 0, texture.width, texture.height }, (Vector2){ bounds.x, bounds.y }, WHITE);

    // Kontrollera om muspekaren är inom knappens område
    if (CheckCollisionPointRec(mousePosition, bounds)) {
        // Ändra färg om knappen är under muspekaren
        DrawRectangleRec(bounds, Fade(GRAY, 0.5f)); // Halvtransparent grå för att indikera hover
        DrawTextureRec(texture, (Rectangle){ 0, 0, texture.width, texture.height }, (Vector2){ bounds.x, bounds.y }, WHITE);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isPressed = true;
        }
    }

    return isPressed;
}
Suit ChooseNewSuit(void) {
    // Funktion för att välja en ny färg när en 8:a spelas
    Suit newSuit = HEARTS;  // Default värde

    // Definiera knapparnas rektanglar
    Rectangle heartButton = { 300, 200, 50, 50 };
    Rectangle diamondButton = { 300, 260, 50, 50 };
    Rectangle clubButton = { 300, 320, 50, 50 };
    Rectangle spadeButton = { 300, 380, 50, 50 };

    while (true) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Rita knapparna med texturer
        if (DrawTexturedButton(heartButton, heart)) { newSuit = HEARTS; break; }
        if (DrawTexturedButton(diamondButton, diamond)) { newSuit = DIAMONDS; break; }
        if (DrawTexturedButton(clubButton, club)) { newSuit = CLUBS; break; }
        if (DrawTexturedButton(spadeButton, spade)) { newSuit = SPADES; break; }
        EndDrawing();
    }

    return newSuit;
}

bool Button(Rectangle bounds, const char *text, Color color) {
    Vector2 mousePosition = GetMousePosition();
    bool isPressed = false;

    // Rita knappen
    DrawRectangleRec(bounds, color);
    DrawRectangleLinesEx(bounds, 2, BLACK); // Knappens ram
    DrawText(text, bounds.x + 10, bounds.y + 10, 20, BLACK);

    // Kontrollera om muspekaren är inom knappens område
    if (CheckCollisionPointRec(mousePosition, bounds)) {
        // Ändra färg om knappen är under muspekaren
        DrawRectangleRec(bounds, GRAY);
        DrawRectangleLinesEx(bounds, 2, BLACK);
        DrawText(text, bounds.x + 10, bounds.y + 10, 20, BLACK);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isPressed = true;
        }
    }

    return isPressed;
}
