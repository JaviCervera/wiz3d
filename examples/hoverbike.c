#include "../src/micron.h"

#define ROTATION_SPEED 32
#define TEXT "Hover Bike by Ptis is licensed under CC Attribution-NonCommercial"

int main()
{
  /* data */
  struct viewer_t* viewer;
  struct light_t* dir_light;
  struct object_t* hoverbike;
  struct material_t* mat0;
  struct material_t* mat1;

  /* setup */
  micron_init();
  screen_set(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = viewer_new();
  viewer->clearmode = CLEAR_SKYBOX;
  viewer->skybox = texture_load("data/skybox.png");
  viewer_move(viewer, 0, 4, -8);
  viewer_turn(viewer, 20, 0, 0);

  /* setup lighting */
  material_setshininesspower(2);
  dir_light = light_new(LIGHT_DIRECTIONAL);
  light_turn(dir_light, 45, -45);

  /* load hoverbike */
  hoverbike = object_load("data/hoverbike.assbin");
  hoverbike->sx = hoverbike->sy = hoverbike->sz = 0.025f;
  mat0 = object_material(hoverbike, 0);
  mat1 = object_material(hoverbike, 1);
  mat0->texture = texture_load("data/bike.png");
  mat0->diffuse = COLOR_WHITE;
  mat0->specular = COLOR_WHITE;
  mat1->texture = texture_load("data/glass.png");
  mat1->diffuse = COLOR_WHITE;
  mat1->specular = COLOR_WHITE;
  mat1->blend = BLEND_ALPHA;

  /* main loop */
  while (screen_opened() && !input_keydown(KEY_ESC))
  {
    /* turn hoverbike */
    object_turn(hoverbike, 0, ROTATION_SPEED * screen_delta(), 0);

    /* draw scene */
    viewer_prepare(viewer);
    object_draw(hoverbike);

    /* draw ui */
    screen_setup2d();
    screen_setdrawcolor(color_rgb(240, 240, 240));
    screen_drawtext(TEXT, (screen_width() - screen_textwidth(TEXT)) / 2, 8);
    screen_refresh();
  }

  /* shutdown */
  micron_finish();
}
