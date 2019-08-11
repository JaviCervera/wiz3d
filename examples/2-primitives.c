#include "../src/beam.h"
#include <stdlib.h>

#define MAX_PRIMITIVES 1000

typedef struct prim_s
{
  float x, y, w, h;
  int color;
  void (* draw)(struct prim_s*);
} prim_t;

void draw_point(prim_t* prim)
{
  SetDrawColor(prim->color);
  DrawPoint(prim->x, prim->y);
}

void draw_line(prim_t* prim)
{
  SetDrawColor(prim->color);
  DrawLine(prim->x, prim->y, prim->w, prim->h);
}

void draw_rect(prim_t* prim)
{
  SetDrawColor(prim->color);
  DrawRect(prim->x, prim->y, prim->w, prim->h);
}

void draw_ellipse(prim_t* prim)
{
  SetDrawColor(prim->color);
  DrawEllipse(prim->x, prim->y, prim->w, prim->h);
}


int main()
{
  /* data */
  prim_t primitives[MAX_PRIMITIVES];
  size_t num_primitives = 0;
  void (* draw_funcs[])(prim_t*) = {draw_point, draw_line, draw_rect, draw_ellipse};
  int i;

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Primitives");

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    /* add primitives until max */
    if (num_primitives < MAX_PRIMITIVES)
    {
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
    for (i = 0; i < num_primitives; ++i)
    {
      primitives[i].draw(&primitives[i]);
    }
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
