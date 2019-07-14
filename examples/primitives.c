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
  screen_setdrawcolor(prim->color);
  screen_drawpoint(prim->x, prim->y);
}

void draw_line(prim_t* prim)
{
  screen_setdrawcolor(prim->color);
  screen_drawline(prim->x, prim->y, prim->w, prim->h);
}

void draw_rect(prim_t* prim)
{
  screen_setdrawcolor(prim->color);
  screen_drawrect(prim->x, prim->y, prim->w, prim->h);
}

void draw_ellipse(prim_t* prim)
{
  screen_setdrawcolor(prim->color);
  screen_drawellipse(prim->x, prim->y, prim->w, prim->h);
}


int main()
{
  /* data */
  prim_t primitives[MAX_PRIMITIVES];
  size_t num_primitives = 0;
  void (* draw_funcs[])(prim_t*) = {draw_point, draw_line, draw_rect, draw_ellipse};
  int i;

  /* setup */
  beam_init();
  screen_set(800, 600, FALSE, TRUE);

  /* main loop */
  while (screen_opened() && !input_keydown(KEY_ESC))
  {
    /* add primitives until max */
    if (num_primitives < MAX_PRIMITIVES)
    {
      primitives[num_primitives].x = rand() % screen_width();
      primitives[num_primitives].y = rand() % screen_height();
      primitives[num_primitives].w = rand() % screen_width();
      primitives[num_primitives].h = rand() % screen_height();
      primitives[num_primitives].color = color_rgb(rand() % 256, rand() % 256, rand() % 256);
      primitives[num_primitives].draw = draw_funcs[rand() % 4];
      ++num_primitives;
    }

    screen_setup2d();
    screen_clear(COLOR_BLACK);
    for (i = 0; i < num_primitives; ++i)
    {
      primitives[i].draw(&primitives[i]);
    }
    screen_refresh();
  }

  /* shutdown */
  beam_finish();
}
