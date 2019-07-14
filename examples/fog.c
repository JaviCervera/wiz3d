#include "../src/beam.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_CUBES (16 * 50)
#define ROTATION_SPEED 32

int main()
{
  /* data */
  struct light_t* dir_light;
  struct viewer_t* viewer;
  struct object_t* cubes[NUM_CUBES];
  int x, z;
  int i;
  char str[STRING_SIZE];

  /* setup */
  beam_init();
  screen_set(800, 600, FALSE, TRUE);

  /* setup lighting */
  dir_light = light_new(LIGHT_DIRECTIONAL);
  light_turn(dir_light, 45, 45);

  /* create and position viewer */
  viewer = viewer_new();
  viewer->clearcolor = COLOR_DARKGRAY;
  viewer_move(viewer, 0, 0, -7);
  viewer->max = 5000;
  viewer->fogenabled = TRUE;
  viewer->fogmax = 20;

  /* create billboards */
  x = -7;
  z = NUM_CUBES / 16 * 2 - 2;
  for (i = 0; i < NUM_CUBES; i += 2)
  {
    struct object_t* cube;

    if (i == 0)
    {
      cube = object_newcube();
      object_material(cube, 0)->diffuse = COLOR_BROWN;
    }
    else
    {
      cube = object_clone(cubes[0]);
    }
    cube->x = x;
    cube->y = -1.5f;
    cube->z = z;
    cubes[i] = cube;

    cube = object_clone(cubes[0]);
    cube->x = x;
    cube->y = 1.5f;
    cube->z = z;
    cubes[i+1] = cube;
    
    x += 2;
    if (x > 7)
    {
      x = -7;
      z -= 2;
    }
  }

  /* main loop */
  while (screen_opened() && !input_keydown(KEY_ESC))
  {
    /* turn objects */
    for (i = 0; i < NUM_CUBES; ++i)
    {
      object_turn(cubes[i], 0, ROTATION_SPEED * screen_delta(), 0);
    }

    /* draw scene */
    viewer_prepare(viewer);
    for (i = 0; i < NUM_CUBES; ++i)
    {
      object_draw(cubes[i]);
    }

    /* draw ui */
    sprintf(str, "%i FPS", screen_fps());
    screen_setup2d();
    screen_drawtext(str, 4, 4);
    screen_refresh();
  }

  /* shutdown */
  beam_finish();
}
