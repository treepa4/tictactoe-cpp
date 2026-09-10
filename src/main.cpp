#include <raylib.h>
Font font;
Color BG = {26, 26, 26, 255};
Color ACCENT_RED = {230, 57, 70, 255};
Color ACCENT_LIGHT = {241, 250, 238, 255};
Color GRID_GRAY = {74, 74, 74, 255};
Color NEON_BLUE = {0, 240, 255, 255};


void DrawGrid(int screensize)
{
    for (int i = 0; i < 2; i++)
    {
        DrawLine(225+(i*150), 75, 225+(i*150), screensize-75, GRID_GRAY);
        DrawLine(75, 225+(i*150), screensize-75, 225+(i*150), GRID_GRAY);
    }
}

enum Cell {EMPTY, X, O};
Cell board[3][3] = {EMPTY};
bool is_player_turn = true;
Cell PlayerMark = X;
Cell AiMark = O;
enum GameStatus {PLAYING, PLAYER_WIN, AI_WIN, DRAW};
GameStatus game_status = PLAYING;
enum Screen {GAME, MENU};
Screen current_screen = MENU; 
int player_score = 0;
int ai_score = 0;

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
                DrawLine(centerX + 65, centerY + 65, centerX - 65, centerY - 65, ACCENT_RED);
                DrawLine(centerX - 65, centerY + 65, centerX + 65, centerY - 65, ACCENT_RED);
            } else if (board[row][col] == O) {
                DrawCircleLines(centerX, centerY, 65, NEON_BLUE);
            }
        }
    }
}


bool CheckDraw() {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == EMPTY) {
                return false;
            }
        }
    }
    return true;
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

void DrawStart() {
    DrawRectangle(150, 300, 300, 100, ACCENT_RED);
    DrawTextEx(font, "START", (Vector2){235, 333}, 32, 8, ACCENT_LIGHT);
}

int main(void)
{
    const int screenSize = 600;
    InitWindow(screenSize, screenSize, "Я СОСУ ЧЛЕН");
    font = LoadFont("assets/PressStart2P-Regular.ttf");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_M)) {
            current_screen = MENU;
        } else if (IsKeyPressed(KEY_G)) {
            current_screen = GAME;
        }
        if (current_screen == GAME) {
            if (game_status == PLAYING) {
                PlayerInput(screenSize);
                AiMove(screenSize);
            }
            
            if (CheckWin(PlayerMark)) {
                game_status = PLAYER_WIN;
            } else if (CheckWin(AiMark)) {
                game_status = AI_WIN;
            } else if (CheckDraw()) {
                game_status = DRAW;
            }
        }

        BeginDrawing();
        ClearBackground(BG);
            if (current_screen == GAME) {
            DrawGrid(screenSize);
            // DrawText("penis!", 190, 200, 20, BEIGE);
            DrawMarks(screenSize);
            }
            else if (current_screen == MENU) {
               DrawText("MENU", 190, 200, 20, ACCENT_LIGHT);
               DrawStart();
            }
        EndDrawing();
        
    }
    UnloadFont(font);
    CloseWindow();        // Close window and OpenGL context
    return 0;
}
