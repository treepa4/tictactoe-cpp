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
Cell PlayerMark = X;
Cell AiMark = O;
enum GameStatus {PLAYING, PLAYER_WIN, AI_WIN, DRAW};
GameStatus game_status = PLAYING;

void PlayerInput(int screenSize) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mouse = GetMousePosition();
                if (mouse.x >= 75 && mouse.x <= screenSize - 75 && mouse.y >= 75 && mouse.y <= screenSize - 75) {
                    int col = ((int)mouse.x - 75) / 150;
                    int row = ((int)mouse.y - 75) / 150;
                    if (board[row][col] == EMPTY && is_player_turn) {
                        board[row][col] = PlayerMark;
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
                    board[row][col] = AiMark;
                    is_player_turn = true;
                    return;
                }
            }
        }
    }
}

void DrawMarks(int screenSize) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
                int centerX = 75 + col * 150 + 75;
                int centerY = 75 + row * 150 + 75;
            if (board[row][col] == X) {
                DrawLine(centerX + 65, centerY + 65, centerX - 65, centerY - 65, RED);
                DrawLine(centerX - 65, centerY + 65, centerX + 65, centerY - 65, RED);
            } else if (board[row][col] == O) {
                DrawCircleLines(centerX, centerY, 65, BLUE);
            }
        }
    }
}


bool CheckWin(Cell mark) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) ||
            (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)) {
            return true;
        }
    }
    if ((board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
        (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)) {
        return true;
    }
    return false;
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
            DrawMarks(screenSize);
        EndDrawing();
        
    }

    
    CloseWindow();        // Close window and OpenGL context
    

    return 0;
}
