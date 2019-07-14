#include "../src/beam.h"
#include "../src/util.h"
#include <stdio.h>

int main()
{
  /* data */
  struct viewer_t* viewer;
  struct light_t* dir_light;
  struct object_t* cube;
  struct material_t* mat;
  char str[STRING_SIZE];

  /* setup */
  beam_init();
  screen_set(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = viewer_new();
  viewer->clearcolor = COLOR_DARKGRAY;
  viewer_move(viewer, 0, 0, -6);

  /* setup lighting */
  dir_light = light_new(LIGHT_DIRECTIONAL);
  light_turn(dir_light, 30, 20);

  /* create a cube */
  cube = object_newcube();
  mat = object_material(cube, 0);
  object_turn(cube, 45, 45, 0);
  mat->diffuse = COLOR_ORANGE;
  mat->shininess = 0;

  /* main loop */
  while (screen_opened() && !input_keydown(KEY_ESC))
  {
    /* update shininess */
    if (input_keydown(KEY_LEFT)) mat->shininess = _clamp(mat->shininess - 0.2f * screen_delta(), 0, 1);
    if (input_keydown(KEY_RIGHT)) mat->shininess = _clamp(mat->shininess + 0.2f * screen_delta(), 0, 1);

    /* draw scene */
    viewer_prepare(viewer);
    object_draw(cube);

    /* draw ui */
    screen_setup2d();
    sprintf(str, "%i FPS", screen_fps());
    screen_drawtext(str, 4, 4);
    sprintf(str, "Shininess: %f (LEFT and RIGHT to change)", mat->shininess);
    screen_drawtext(str, 4, 16);
    screen_refresh();
  }

  /* shutdown */
  beam_finish();
}
