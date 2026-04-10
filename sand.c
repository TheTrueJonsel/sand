#include "raylib.h"
#include <string.h>

#define WIDTH 600
#define HEIGHT 600
#define ROWS 60
#define COLS 60
#define PIXELWIDTH 10

const char *title = "Sand";
Vector2 mousePosition;

int bufferA[ROWS][COLS];
int bufferB[ROWS][COLS];

int (*currentBuffer)[COLS];
int (*nextBuffer)[COLS];

void clearBuffer(int (*buffer)[COLS]){
    memset(buffer, 0, sizeof(bufferA));
}

void swapBuffers(){
    int (*temp)[COLS] = currentBuffer;
    currentBuffer = nextBuffer;
    nextBuffer = temp;
    clearBuffer(nextBuffer);
}

void setup(){
    InitWindow(WIDTH, HEIGHT, title);
    SetTargetFPS(6);
    currentBuffer = bufferA;
    nextBuffer = bufferB;
    clearBuffer(currentBuffer);
    clearBuffer(nextBuffer);
    currentBuffer[20][20] = 1; // remove after testing
}

void drawGame(){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            if(currentBuffer[i][j] == 1){
                DrawRectangle(j * PIXELWIDTH, i * PIXELWIDTH, PIXELWIDTH, PIXELWIDTH, RAYWHITE);
            }
        }
    }
}

void updateGame(){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS - 1; j++){
            if(currentBuffer[i][j] == 1){
                if(currentBuffer[i+1][j] == 0){
                    nextBuffer[i][j] = 0;
                    nextBuffer[i+1][j] = 1;
                }
            }
        }
    }
}

int main(){
    setup();

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
            updateGame();
            drawGame();
            swapBuffers();
        EndDrawing();
    }

    CloseWindow();
}