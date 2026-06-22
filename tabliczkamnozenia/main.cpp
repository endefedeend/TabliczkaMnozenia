#include "raylib.h"

constexpr int W = 1000, H = 1000;
constexpr int N = 10, C = 70, FONT = 28;
constexpr int SX = (W - C * N) / 3;
constexpr int SY = 195;

int hoverX = -1, hoverY = -1;

Color header[] = {
    DARKGRAY, RED, ORANGE, GOLD, LIME, GREEN,
    SKYBLUE, BLUE, PURPLE, PINK, VIOLET
};

const char* CellText(int x, int y) {
    if (x == 0 && y == 0) return "x";
    if (x == 0) return TextFormat("%d", y);
    if (y == 0) return TextFormat("%d", x);
    return TextFormat("%d", x * y);
}

Color CellColor(int x, int y) {
    if (x == hoverX && y == hoverY) return BLUE;
    if ((y == 0 && x == hoverX) || (x == 0 && y == hoverY)) return DARKBROWN;
    if (y == 0) return header[x];
    if (x == 0) return header[y];
    return {255, 245, 210, 255};
}

void DrawTextCentered(const char* text, Rectangle r, int size, Color color) {
    int width = MeasureText(text, size);

    DrawText(
        text,
        (int)(r.x + (r.width - width) / 2),
        (int)(r.y + (r.height - size) / 2),
        size,
        color
    );
}
void UpdateHover() {
    hoverX = (GetMouseX() - SX) / C;
    hoverY = (GetMouseY() - SY) / C;

    if (hoverX < 1 || hoverX > N || hoverY < 1 || hoverY > N)
        hoverX = hoverY = -1;
}

void DrawCell(int x, int y) {
    Rectangle r = {
        (float)(SX + x * C),
        (float)(SY + y * C),
        C - 5.0f,
        C - 5.0f
    };

    DrawRectangleRounded(r, 0.15f, 8, CellColor(x, y));
    DrawRectangleRoundedLines(r, 0.15f, 8, DARKGRAY);

    DrawTextCentered(
        CellText(x, y),
        r,
        FONT,
        (x == 0 || y == 0) ? WHITE : DARKBLUE
    );
}

void DrawResult() {
    DrawText(
        hoverX == -1
            ? "Najedz myszka na pole!"
            : TextFormat("%d x %d = %d", hoverY, hoverX, hoverX * hoverY),
        740,
        90,
        hoverX == -1 ? 14 : 42,
        DARKGREEN
    );
}

void DrawTable() {
    ClearBackground({220, 245, 210, 255});
    UpdateHover();

    DrawText("TABLICZKA", 280, 35, 70, ORANGE);
    DrawText("MNOZENIA", 320, 105, 60, SKYBLUE);

    DrawRectangleRounded(
        {(float)SX - 25, (float)SY - 25, C * (N + 1) + 45.0f, C * (N + 1) + 45.0f},
        0.02f,
        8,
        {160, 120, 80, 255}
    );

    for (int y = 0; y <= N; y++)
        for (int x = 0; x <= N; x++)
            DrawCell(x, y);

    DrawResult();
}

int main() {
    InitWindow(W, H, "Kolorowa tabliczka mnozenia");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawTable();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
