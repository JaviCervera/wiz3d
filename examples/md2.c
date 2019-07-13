#include "../src/micron.h"
#include <stdio.h>

int main()
{
  /* data */
  struct viewer_t* viewer;
  struct object_t* md2;
  bool_t walking;
  bool_t space_down;
  char str[STRING_SIZE];

  /* setup */
  micron_init();
  screen_set(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = viewer_new();
  viewer->clearcolor = COLOR_DARKGRAY;
  viewer_move(viewer, 0, 2, -4);
  viewer_turn(viewer, 15, 0, 0);

  /* load md2 */
  md2 = object_load("data/german.md2");
  md2->animmode = ANIM_LOOP;
  object_turn(md2, 0, 90, 0);
  object_material(md2, 0)->texture = texture_load("data/german.png"); /* this shouldn't be necessary */

  /* main loop */
  while (screen_opened() && !input_keydown(KEY_ESC))
  {
    /* update animation */
    if (input_keydown(KEY_SPACE))
    {
      if (!space_down) walking = !walking;
      space_down = TRUE;
    }
    else
    {
      space_down = FALSE;
    }
    if (walking)
    {
      md2->animmin = 31;
      md2->animmax = 0; // 51
    }
    else
    {
      md2->animmin = 0;
      md2->animmax = 25;
    }

    /* draw scene */
    viewer_prepare(viewer);
    object_draw(md2);

    /* draw ui */
    screen_setup2d();
    sprintf(str, "%i FPS", screen_fps());
    screen_drawtext(str, 4, 4);
    sprintf(str, "Frame: %i", (int)md2->animframe);
    screen_drawtext(str, 4, 16);
    screen_refresh();
  }

  /* shutdown */
  micron_finish();
}
