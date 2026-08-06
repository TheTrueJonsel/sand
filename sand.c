#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

// TODO
// I finished the updateGrid() function, now I only need to draw the updated grid based on the information in the now accurate grid array and I am done

int *grid;
int *nextGrid;
int rows, cols;

// Initializing the window
const int screenWidth = 800, screenHeight = 800;
const int cellSize = 10;

void updateGrid(){
    for(int i = rows - 1; i >= 0; i--){
        for(int j = 0; j < cols; j++){
            if(grid[i * rows + j] == 1){
            // This code is executed if there is a sand pixel at the current grid position
                // Checking if I am not in the last row and the pixel right under the current pixel is empty and if it is, then I move the sand pixel down one position
                // If not, then I check if I am not in the last row and the position left-below the current pixel and move the current sand pixel there if it is free
                // If not, then I check if I am not in the last row and the position right-below the current pixel and move the current sandpixel there if it is free
                if(grid[(i + 1) * rows + j] == 0){
                    nextGrid[i * rows + j] = 0;
                    nextGrid[(i + 1) * rows + j] = 1;   
                } else if(j - 1 >= 0 && grid[(i + 1) * rows + j] == 0){
                    nextGrid[i * rows + j] = 0;
                    nextGrid[(i + 1) * rows + j -1] = 1;   
                } else if(j + 1 <= rows - 1 && grid[(i + 1) * rows + j + 1] == 0){
                    nextGrid[i * rows + j] = 0;
                    nextGrid[(i + 1) * rows + j + 1] = 1;   
                } else {
                // This code is executed if I am in the last row or if there are no free spaces under me.
                    nextGrid[i * rows + j] = 1;
                }
            }
        }
    }
    // copying the newly calculated nextGrid into grid and resetting it to 0 afterward
    for(int i = 0; i < rows * cols; i++){
        grid[i] = nextGrid[i];
        nextGrid[i] = 0;
    }
}

void drawGrid(){

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(grid[(i * cols) + j] == 1){
                DrawRectangle(j * 10,i * 10,40,40,YELLOW);
            } else if(grid[(i * cols) + j] == 0){
                DrawRectangle(j * 10,i * 10,40,40,BLACK);
            }
        }
    }
}

void initGrid(){
    cols = screenWidth / cellSize;
    rows = screenHeight / cellSize;

    // Allocating memory for the two grids
    grid = (int *) malloc(rows * cols * sizeof(int));
    nextGrid = (int *) malloc(rows *cols * sizeof(int)); 

    // Initializing the values of both arrays to 0
    for(int i = 0; i < rows * cols; i++){
        grid[i] = 0;
        nextGrid[i] = 0;
    }
}

void mouseHandler(){
    // Setting the Mouse button that was clicked on to active
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        Vector2 mousePos = GetMousePosition();
        int x = mousePos.x / cellSize;
        int y = mousePos.y / cellSize;
        grid[y * cols + x] = 1;
        // printf("REGISTERED CLICK AT:\nX = %f\n Y = %f\n", mousePos.x, mousePos.y);
    }

}

int main(){

    InitWindow(screenWidth, screenHeight, "Falling Sand Simulation");
    SetTargetFPS(60);

    initGrid();

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        mouseHandler();
        updateGrid();
        drawGrid();
        EndDrawing();
    }

    free(grid);
    free(nextGrid);
    CloseWindow();
    return 0;
}