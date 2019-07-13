#include "../src/micron.h"

int main()
{
  /* data */
  struct object_t* floor;
  struct object_t* ball;
  struct object_t* block;
  struct object_t* ball_shadow;
  struct object_t* block_shadow;
  struct viewer_t* viewer;
  struct light_t* dir_light;
  int direction = 1;

  /* setup */
  micron_init();
  screen_set(800, 600, FALSE, TRUE);

  /* create floor */
  floor = object_newcube();
  object_move(floor, 0, -0.5f, 4);
  floor->colmode = COL_BOX;
  floor->sx = floor->sz = 20;
  object_material(floor, 0)->diffuse = COLOR_BLUE;

  /* load ball */
  ball = object_load("data/sphere.assbin");
  object_move(ball, 0, 0.5f, -4);
  ball->colmode = COL_SPHERE;
  ball->radius = 0.5f;
  object_material(ball, 0)->diffuse = COLOR_RED;

  /* create block */
  block = object_newcube();
  object_move(block, 0, 2, 0);
  block->colmode = COL_BOX;
  block->sx = block->sy = 4;
  object_material(block, 0)->diffuse = COLOR_LIGHTGRAY;

  /* create ball shadow */
  ball_shadow = object_newquad();
  ball_shadow->pitch = 90;
  object_material(ball_shadow, 0)->texture = texture_load("data/circle_shadow.png");
  object_material(ball_shadow, 0)->diffuse = COLOR_BLACK;
  object_material(ball_shadow, 0)->blend = BLEND_ALPHA;

  /* create block shadow */
  block_shadow = object_newquad();
  block_shadow->pitch = 90;
  block_shadow->sx = 4;
  object_material(block_shadow, 0)->diffuse = COLOR_LIGHTGRAY;
  object_material(block_shadow, 0)->blend = BLEND_MUL;

  /* create and position viewer */
  viewer = viewer_new();
  viewer_move(viewer, 0, 7, -8);
  viewer_turn(viewer, 45, 0, 0);

  /* setup lighting */
  light_setambient(COLOR_LIGHTGRAY);
  dir_light = light_new(LIGHT_DIRECTIONAL);
  dir_light->pitch = 15;
  dir_light->yaw = 60;

  /* main loop */
  while (screen_opened() && !input_keydown(KEY_ESC))
  {
    /* move ball */
    if (input_keydown(KEY_UP)) object_move(ball, 0, 0, 2 * screen_delta());
    if (input_keydown(KEY_DOWN)) object_move(ball, 0, 0, -2 * screen_delta());
    if (input_keydown(KEY_LEFT)) object_move(ball, -2 * screen_delta(), 0, 0);
    if (input_keydown(KEY_RIGHT)) object_move(ball, 2 * screen_delta(), 0, 0);

    /* move block */
    object_move(block, 0, 2 * direction * screen_delta(), 0);
    if (block->y >= 4)
    {
      block->y = 4;
      direction = -1;
    }
    if (object_collidesobject(block, floor) || object_collidesobject(block, ball))
    {
      direction = 1;
    }

    /* update shadows */
    ball_shadow->x = ball->x;
    ball_shadow->z = ball->z;
    block_shadow->x = block->x;
    block_shadow->z = block->z;

    /* draw scene */
    viewer_prepare(viewer);
    object_draw(floor);
    object_draw(ball);
    object_draw(block);
    object_draw(block_shadow);
    object_draw(ball_shadow);

    /* draw ui */
    screen_refresh();
  }

  /* shutdown */
  micron_finish();
}
