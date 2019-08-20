#include "../src/spark.h"
#include <stdlib.h>

#define MAX_PRIMITIVES 1000

typedef struct SPrimitive {
  float x, y, w, h;
  int color;
  void (* draw)(struct SPrimitive*);
} Primitive;

void DrawPoint(Primitive* prim) {
  spSetDrawColor(prim->color);
  spDrawPoint(prim->x, prim->y);
}

void DrawLine(Primitive* prim) {
  spSetDrawColor(prim->color);
  spDrawLine(prim->x, prim->y, prim->w, prim->h);
}

void DrawRect(Primitive* prim) {
  spSetDrawColor(prim->color);
  spDrawRect(prim->x, prim->y, prim->w, prim->h);
}

void DrawEllipse(Primitive* prim) {
  spSetDrawColor(prim->color);
  spDrawEllipse(prim->x, prim->y, prim->w, prim->h);
}


int main() {
  /* Data */
  Primitive primitives[MAX_PRIMITIVES];
  size_t num_primitives = 0;
  void (* draw_funcs[])(Primitive*) = {DrawPoint, DrawLine, DrawRect, DrawEllipse};
  int i;

  /* Setup */
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("Primitives");

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    /* add primitives until max */
    if (num_primitives < MAX_PRIMITIVES) {
      primitives[num_primitives].x = rand() % spGetScreenWidth();
      primitives[num_primitives].y = rand() % spGetScreenHeight();
      primitives[num_primitives].w = rand() % spGetScreenWidth();
      primitives[num_primitives].h = rand() % spGetScreenHeight();
      primitives[num_primitives].color = spGetRGB(rand() % 256, rand() % 256, rand() % 256);
      primitives[num_primitives].draw = draw_funcs[rand() % 4];
      ++num_primitives;
    }

    spSetup2D();
    spClearScreen(COLOR_BLACK);
    for (i = 0; i < num_primitives; ++i) {
      primitives[i].draw(&primitives[i]);
    }
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
