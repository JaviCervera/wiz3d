#include "../src/beam.h"
#include <stdlib.h>

#define MAX_PRIMITIVES 1000

typedef struct SPrimitive {
  float x, y, w, h;
  int color;
  void (* draw)(struct SPrimitive*);
} Primitive;

void DrawPoint(Primitive* prim) {
  bmSetDrawColor(prim->color);
  bmDrawPoint(prim->x, prim->y);
}

void DrawLine(Primitive* prim) {
  bmSetDrawColor(prim->color);
  bmDrawLine(prim->x, prim->y, prim->w, prim->h);
}

void DrawRect(Primitive* prim) {
  bmSetDrawColor(prim->color);
  bmDrawRect(prim->x, prim->y, prim->w, prim->h);
}

void DrawEllipse(Primitive* prim) {
  bmSetDrawColor(prim->color);
  bmDrawEllipse(prim->x, prim->y, prim->w, prim->h);
}


int main() {
  /* Data */
  Primitive primitives[MAX_PRIMITIVES];
  size_t num_primitives = 0;
  void (* draw_funcs[])(Primitive*) = {DrawPoint, DrawLine, DrawRect, DrawEllipse};
  int i;

  /* Setup */
  bmInitBeam();
  bmSetScreen(800, 600, FALSE, TRUE);
  bmSetScreenTitle("Primitives");

  /* Main loop */
  while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
    /* add primitives until max */
    if (num_primitives < MAX_PRIMITIVES) {
      primitives[num_primitives].x = rand() % bmGetScreenWidth();
      primitives[num_primitives].y = rand() % bmGetScreenHeight();
      primitives[num_primitives].w = rand() % bmGetScreenWidth();
      primitives[num_primitives].h = rand() % bmGetScreenHeight();
      primitives[num_primitives].color = bmGetRGB(rand() % 256, rand() % 256, rand() % 256);
      primitives[num_primitives].draw = draw_funcs[rand() % 4];
      ++num_primitives;
    }

    bmSetup2D();
    bmClearScreen(COLOR_BLACK);
    for (i = 0; i < num_primitives; ++i) {
      primitives[i].draw(&primitives[i]);
    }
    bmRefreshScreen();
  }

  /* Shutdown */
  bmShutdownBeam();
}
