#include "rendering.h"
#include <stdio.h>
#include <stdlib.h>
#include "deck.h"
#include "card.h"
#include "gameplay.h"
//#include "rendering.h"
#include <string.h>
#include <raylib.h>
#include <unistd.h>
#include <limits.h>

Texture2D heart, diamond, club, spade;
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
