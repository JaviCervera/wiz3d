#include "../src/beam.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_BILLBOARDS 64
#define ROTATION_SPEED 32

int main()
{
  /* data */
  struct viewer_t* viewer;
  struct texture_t* tex;
  struct object_t* billboards[NUM_BILLBOARDS];
  int x, z;
  int i;
  char str[STRING_SIZE];

  /* setup */
  beam_init();
  screen_set(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = viewer_new();
  viewer->clearcolor = COLOR_WHITE;
  viewer_turn(viewer, 45, -45, 0);

  /* load texture */
  tex = texture_load("data/smile.png");

  /* create billboards */
  x = z = -8;
  for (i = 0; i < NUM_BILLBOARDS; ++i)
  {
    billboards[i] = object_newquad();
    billboards[i]->billboard = BILLBOARD_FACE;
    billboards[i]->x = x;
    billboards[i]->z = z;
    object_material(billboards[i], 0)->texture = tex;
    object_material(billboards[i], 0)->diffuse = color_rgb(rand() % 256, rand() % 256, rand() % 256);
    object_material(billboards[i], 0)->blend = BLEND_ALPHA;
    
    x += 2;
    if (x >= 8)
    {
      x = -8;
      z += 2;
    }
  }

  /* main loop */
  while (screen_opened() && !input_keydown(KEY_ESC))
  {
    /* update viewer */
    viewer_turn(viewer, 0, ROTATION_SPEED * screen_delta(), 0);
    viewer->x = viewer->y = viewer->z = 0;
    viewer_move(viewer, 0, 0, -8);

    /* draw scene */
    viewer_prepare(viewer);
    for (i = 0; i < NUM_BILLBOARDS; ++i)
    {
      object_draw(billboards[i]);
    }

    /* draw ui */
    sprintf(str, "%i FPS", screen_fps());
    screen_setup2d();
    screen_setdrawcolor(COLOR_BLACK);
    screen_drawtext(str, 4, 4);
    screen_refresh();
  }

  /* shutdown */
  beam_finish();
}
