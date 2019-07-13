#include "../src/micron.h"
#include <math.h>

#define ROTATION_SPEED 32
#define TEXT "Frank by misterdevious is licensed under CC Attribution-NonCommercial-ShareAlike"

int main()
{
  /* data */
  struct viewer_t* viewer;
  struct light_t* dir_light;
  struct light_t* point_light1;
  struct light_t* point_light2;
  struct object_t* angel;
  float value = 0;

  /* setup */
  micron_init();
  screen_set(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = viewer_new();
  viewer->clearcolor = color_rgb(15, 15, 15);
  viewer_move(viewer, 7, 7, -7);
  viewer_turn(viewer, 37.5f, -45, 0);

  /* setup lighting */
  light_setambient(color_rgb(15, 15, 15));
  dir_light = light_new(LIGHT_DIRECTIONAL);
  dir_light->color = color_rgb(100, 100, 100);
  point_light1 = light_new(LIGHT_POINT);
  light_move(point_light1, 0, 0, -2);
  point_light1->color = color_rgb(255, 100, 0);
  point_light2 = light_new(LIGHT_POINT);
  light_move(point_light2, 0, 8, 4);
  point_light2->color = color_rgb(0, 100, 255);

  /* load object (contains embedded texture) */
  angel = object_load("data/angel.assbin");
  object_turn(angel, 90, 0, 0);

  /* main loop */
  while (screen_opened() && !input_keydown(KEY_ESC))
  {
    float s, c;

    /* rotate statue */
    object_turn(angel, 0, ROTATION_SPEED * screen_delta(), 0);

    /* update lighting */
    value += screen_delta();
    s = 0.5f + fabsf(sinf(value)) * 0.5f;
    c = 0.5f + fabsf(cosf(value)) * 0.5f;
    point_light1->range = 10 * s;
    point_light2->range = 10 * c;

    /* draw scene */
    viewer_prepare(viewer);
    object_draw(angel);

    /* draw ui */
    screen_setup2d();
    screen_setdrawcolor(color_rgb(240, 240, 240));
    screen_drawtext(TEXT, (screen_width() - screen_textwidth(TEXT)) / 2, 8);
    screen_refresh();
  }

  /* shutdown */
  micron_finish();
}
