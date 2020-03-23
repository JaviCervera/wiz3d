#include "../src/wiz3d.h"
#include <stdlib.h>

#define MAX_PRIMITIVES 1000

typedef struct SPrimitive {
    float x, y, w, h;
    int color;
    void (* draw)(struct SPrimitive*);
} Primitive;

void DrawPoint(Primitive* prim) {
    wzSetDrawColor(prim->color);
    wzDrawPoint(prim->x, prim->y);
}

void DrawLine(Primitive* prim) {
    wzSetDrawColor(prim->color);
    wzDrawLine(prim->x, prim->y, prim->w, prim->h);
}

void DrawRect(Primitive* prim) {
    wzSetDrawColor(prim->color);
    wzDrawRect(prim->x, prim->y, prim->w, prim->h);
}

void DrawEllipse(Primitive* prim) {
    wzSetDrawColor(prim->color);
    wzDrawEllipse(prim->x, prim->y, prim->w, prim->h);
}


int main() {
    /* Data */
    Primitive primitives[MAX_PRIMITIVES];
    size_t num_primitives = 0;
    void (* draw_funcs[])(Primitive*) = {DrawPoint, DrawLine, DrawRect, DrawEllipse};
    int i;

    /* Setup */
    wzInitWiz3D();
    wzSetScreen(800, 600, FALSE, TRUE);
    wzSetScreenTitle("Primitives");

    /* Main loop */
    while (wzIsScreenOpened() && !wzIsKeyPressed(KEY_ESC)) {
        /* add primitives until max */
        if (num_primitives < MAX_PRIMITIVES) {
            primitives[num_primitives].x = rand() % wzGetScreenWidth();
            primitives[num_primitives].y = rand() % wzGetScreenHeight();
            primitives[num_primitives].w = rand() % wzGetScreenWidth();
            primitives[num_primitives].h = rand() % wzGetScreenHeight();
            primitives[num_primitives].color = wzGetRGB(rand() % 256, rand() % 256, rand() % 256);
            primitives[num_primitives].draw = draw_funcs[rand() % 4];
            ++num_primitives;
        }

        wzSetup2D();
        wzClearScreen(COLOR_BLACK);
        for (i = 0; i < num_primitives; ++i) {
            primitives[i].draw(&primitives[i]);
        }
        wzRefreshScreen();
    }

    /* Shutdown */
    wzShutdownWiz3D();
}
