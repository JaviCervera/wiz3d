#include "../src/beam.h"
#include <stdlib.h>

#define MAX_PRIMITIVES 1000

typedef struct SPrimitive {
  float x, y, w, h;
  int color;
  void (* draw)(struct SPrimitive*);
} Primitive;

void DrawPointPrimitive(Primitive* prim) {
  SetDrawColor(prim->color);
  DrawPoint(prim->x, prim->y);
}

void DrawLinePrimitive(Primitive* prim) {
  SetDrawColor(prim->color);
  DrawLine(prim->x, prim->y, prim->w, prim->h);
}

void DrawRectPrimitive(Primitive* prim) {
  SetDrawColor(prim->color);
  DrawRect(prim->x, prim->y, prim->w, prim->h);
}

void DrawEllipsePrimitive(Primitive* prim) {
  SetDrawColor(prim->color);
  DrawEllipse(prim->x, prim->y, prim->w, prim->h);
}


int main() {
  /* Data */
  Primitive primitives[MAX_PRIMITIVES];
  size_t num_primitives = 0;
  void (* draw_funcs[])(Primitive*) = {DrawPointPrimitive, DrawLinePrimitive, DrawRectPrimitive, DrawEllipsePrimitive};
  int i;

  /* Setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Primitives");

  /* Main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    /* add primitives until max */
    if (num_primitives < MAX_PRIMITIVES) {
      primitives[num_primitives].x = rand() % GetScreenWidth();
      primitives[num_primitives].y = rand() % GetScreenHeight();
      primitives[num_primitives].w = rand() % GetScreenWidth();
      primitives[num_primitives].h = rand() % GetScreenHeight();
      primitives[num_primitives].color = GetRGB(rand() % 256, rand() % 256, rand() % 256);
      primitives[num_primitives].draw = draw_funcs[rand() % 4];
      ++num_primitives;
    }

    Setup2D();
    ClearScreen(COLOR_BLACK);
    for (i = 0; i < num_primitives; ++i) {
      primitives[i].draw(&primitives[i]);
    }
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownBeam();
}
