#include "../src/beam.h"
#include <stdio.h>

#define ROTATION_SPEED 90

int main()
{
  /* data */
  struct viewer_t* viewer;
  struct light_t* dir_light;
  struct object_t* cube;
  char str[STRING_SIZE];

  /* setup */
  beam_init();
  screen_set(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = viewer_new();
  viewer->clearcolor = color_rgb(15, 15, 15);
  viewer_move(viewer, 0, 2, -2);
  viewer_turn(viewer, 45, 0, 0);

  /* setup lighting */
  dir_light = light_new(LIGHT_DIRECTIONAL);
  light_turn(dir_light, 45, 45);

  /* create a cube */
  cube = object_newcube();
  object_material(cube, 0)->texture = texture_load("data/box.png");

  /* main loop */
  while (screen_opened() && !input_keydown(KEY_ESC))
  {
    object_turn(cube, 0, ROTATION_SPEED * screen_delta(), 0);

    /* draw scene */
    viewer_prepare(viewer);
    object_draw(cube);

    /* draw ui */
    sprintf(str, "%i FPS", screen_fps());
    screen_setup2d();
    screen_drawtext(str, 4, 4);
    screen_refresh();
  }

  /* shutdown */
  beam_finish();
}
