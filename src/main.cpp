#include <raylib.h>

void DrawGrid(int screensize)
{
    for (int i = 0; i < 2; i++)
    {
        DrawLine(225+(i*150), 75, 225+(i*150), screensize-75, BEIGE);
        DrawLine(75, 225+(i*150), screensize-75, 225+(i*150), BEIGE);
    }
}
enum Cell {EMPTY, X, O};
Cell board[3][3] = {EMPTY};
bool is_player_turn = true;


void PlayerInput(int screenSize) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mouse = GetMousePosition();
                if (mouse.x >= 75 && mouse.x <= screenSize - 75 && mouse.y >= 75 && mouse.y <= screenSize - 75) {
                    int col = ((int)mouse.x - 75) / 150;
                    int row = ((int)mouse.y - 75) / 150;
                    if (board[row][col] == EMPTY && is_player_turn) {
                        board[row][col] = X;
                        is_player_turn = false;
                    }
                }
            }
}

void AiMove(int screenSize) {
    if (!is_player_turn) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = O;
                    is_player_turn = true;
                    return;
                }
            }
        }
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
        PlayerInput(screenSize);
        AiMove(screenSize);
        BeginDrawing();

            ClearBackground(WHITE);
            DrawGrid(screenSize);
            // DrawText("penis!", 190, 200, 20, BEIGE);
            
        EndDrawing();
        
    }

    
    CloseWindow();        // Close window and OpenGL context
    

    return 0;
}
