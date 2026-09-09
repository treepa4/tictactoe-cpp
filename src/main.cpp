#include <raylib.h>

void DrawGrid(int screensize)
{
    for (int i = 0; i < 2; i++)
    {
        DrawLine(225+(i*150), 75, 225+(i*150), screensize-75, BEIGE);
        DrawLine(75, 225+(i*150), screensize-75, 225+(i*150), BEIGE);
    }

}


int main(void)
{
    const int screenSize = 600;

    InitWindow(screenSize, screenSize, "Я СОСУ ЧЛЕН");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        BeginDrawing();

            ClearBackground(WHITE);
            DrawGrid(screenSize);
            // DrawText("penis!", 190, 200, 20, BEIGE);

        EndDrawing();
        
    }

    
    CloseWindow();        // Close window and OpenGL context
    

    return 0;
}
