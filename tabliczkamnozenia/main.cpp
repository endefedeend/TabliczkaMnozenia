#include "raylib.h"
#include <string>

const int W = 1000, H = 1000;
const int N = 10, C = 70;
const int FONT = 28;

int startX, startY;
int hoverX = -1, hoverY = -1;

Color header[] = {
    DARKGRAY, RED, ORANGE, GOLD, LIME, GREEN,
    SKYBLUE, BLUE, PURPLE, PINK, VIOLET
};

std::string CellText(int x, int y) {
    if (x == 0 && y == 0) return "x";
    if (y == 0) return std::to_string(x);
    if (x == 0) return std::to_string(y);
    return std::to_string(x * y);
}

Color CellColor(int x, int y) {
    if (x == hoverX && y == hoverY) return BLUE;
    if ((y == 0 && x == hoverX) || (x == 0 && y == hoverY)) return DARKBROWN;
    if (y == 0) return header[x];
    if (x == 0) return header[y];
    return {255, 245, 210, 255};
}

void DrawCenteredText(const std::string& text, Rectangle r, int size, Color color) {
    int width = MeasureText(text.c_str(), size);

    DrawText(
        text.c_str(),
        r.x + (r.width - width) / 2,
        r.y + (r.height - size) / 2,
        size,
        color
    );
}

void UpdateHover() {
    int x = (GetMouseX() - startX) / C;
    int y = (GetMouseY() - startY) / C;

    if (x >= 1 && x <= N && y >= 1 && y <= N) {
        hoverX = x;
        hoverY = y;
    } else {
        hoverX = hoverY = -1;
    }
}

void DrawCell(int x, int y) {
    Rectangle r = {
        (float)(startX + x * C),
        (float)(startY + y * C),
        C - 5.0f,
        C - 5.0f
    };

    DrawRectangleRounded(r, 0.15f, 8, CellColor(x, y));
    DrawRectangleRoundedLines(r, 0.15f, 8, DARKGRAY);

    Color textColor = (x == 0 || y == 0) ? WHITE : DARKBLUE;
    DrawCenteredText(CellText(x, y), r, FONT, textColor);
}

void DrawResult() {
    if (hoverX == -1) {
        DrawText("Najedz myszka na pole!", 740, 90, 14, DARKGREEN);
        return;
    }

    std::string text =
        std::to_string(hoverY) + " x " +
        std::to_string(hoverX) + " = " +
        std::to_string(hoverX * hoverY);

    DrawText(text.c_str(), 740, 90, 42, DARKGREEN);
}

void DrawTable() {
    ClearBackground({220, 245, 210, 255});
    UpdateHover();

    DrawText("TABLICZKA", 280, 35, 70, ORANGE);
    DrawText("MNOZENIA", 320, 105, 60, SKYBLUE);

    Rectangle frame = {
        (float)(startX - 25),
        (float)(startY - 25),
        (float)(C * (N + 1) + 45),
        (float)(C * (N + 1) + 45)
    };

    DrawRectangleRounded(frame, 0.02f, 8, {160, 120, 80, 255});

    for (int y = 0; y <= N; y++) {
        for (int x = 0; x <= N; x++) {
            DrawCell(x, y);
        }
    }

    DrawResult();
}

int main() {
    startX = (W - C * N) / 3;
    startY = 195;

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
