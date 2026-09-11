#include <raylib.h>
#include <algorithm>

Font font;
Color BG = {26, 26, 26, 255};
Color ACCENT_RED = {230, 57, 70, 255};
Color ACCENT_LIGHT = {241, 250, 238, 255};
Color GRID_GRAY = {74, 74, 74, 255};
Color NEON_BLUE = {0, 240, 255, 255};

enum Cell {EMPTY, X, O};
Cell board[3][3] = {EMPTY};
bool is_player_turn = true;
Cell PlayerMark = X;
Cell AiMark = O;
enum GameStatus {PLAYING, PLAYER_WIN, AI_WIN, DRAW};
GameStatus game_status = PLAYING;
enum Screen {GAME, MENU};
Screen current_screen = MENU;
const int screenSize = 600;
int player_score = 0;
int ai_score = 0;
int rectWidth = 300;
int rectHeight = 100;
int rectX = (screenSize / 2) - 150;
int rectY = screenSize / 2;

void DrawGrid()
{
    for (int i = 0; i < 2; i++)
    {
        DrawLine(225+(i*150), 75, 225+(i*150), 600-75, GRID_GRAY);
        DrawLine(75, 225+(i*150), 600-75, 225+(i*150), GRID_GRAY);
    }
}

void DrawMarks() {
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

int Minimax(bool isMaximizing) {
    if (CheckWin(AiMark)) return 1;
    if (CheckWin(PlayerMark)) return -1;
    if (CheckDraw()) return 0;

    if (isMaximizing) {
        int best = -1000;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = AiMark;
                    int score = Minimax(false);
                    board[row][col] = EMPTY;
                    best = std::max(best, score);
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = PlayerMark;
                    int score = Minimax(true);
                    board[row][col] = EMPTY;
                    best = std::min(best, score);
                }
            }
        }
        return best;
    }
}

void DrawStart() {
    DrawRectangle(rectX, rectY, rectWidth, rectHeight, ACCENT_RED);
    int rectCenterX = rectX + rectWidth / 2;
    int rectCenterY = rectY + rectHeight / 2;
    Vector2 startTextSize = MeasureTextEx(font, "START", 32, 8);
    Vector2 startPos = { rectCenterX - startTextSize.x / 2, rectCenterY - startTextSize.y / 2 };
    DrawTextEx(font, "START", startPos, 32, 8, ACCENT_LIGHT);
    Vector2 menuTextSize = MeasureTextEx(font, "MENU", 26, 4);
    Vector2 menuPos = { screenSize / 2.0f - menuTextSize.x / 2, 200 };
    DrawTextEx(font, "MENU", menuPos, 26, 4, ACCENT_RED);
}

void MenuInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 m = GetMousePosition();
        if (m.x >= rectX && m.x <= rectX + rectWidth &&
            m.y >= rectY && m.y <= rectY + rectHeight) {
            current_screen = GAME;
        }
    }
}

void PlayerInput() {
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

void AiMove() {
    if (!is_player_turn) {
        int bestScore = -1000;
        int bestRow = -1, bestCol = -1;

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == EMPTY) {
                    board[row][col] = AiMark;
                    int score = Minimax(false);
                    board[row][col] = EMPTY;

                    if (score > bestScore) {
                        bestScore = score;
                        bestRow = row;
                        bestCol = col;
                    }
                }
            }
        }

        if (bestRow != -1) {
            board[bestRow][bestCol] = AiMark;
            is_player_turn = true;
        }
    }
}

void ResetGame() {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            board[row][col] = EMPTY;
        }
    }
    is_player_turn = true;
    game_status = PLAYING;
}

int main(void)
{
    InitWindow(screenSize, screenSize, "Tici-Taki");
    font = LoadFont("assets/PressStart2P-Regular.ttf");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_M)) {
            current_screen = MENU;
        } else if (IsKeyPressed(KEY_G)) {
            current_screen = GAME;
        }
        if (IsKeyPressed(KEY_R)) {
            ResetGame();
        }
        if (current_screen == GAME) {
            if (game_status == PLAYING) {
                PlayerInput();
                AiMove();
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
            DrawGrid();
            DrawMarks();
            }
            else if (current_screen == MENU) {
               DrawStart();
               MenuInput();
            }
        EndDrawing();

    }
    UnloadFont(font);
    CloseWindow();
    return 0;
}