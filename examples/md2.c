#include "../src/beam.h"
#include <stdio.h>

int main()
{
  /* data */
  Viewer* viewer;
  Object* md2;
  bool_t walking;
  bool_t space_down;
  char str[STRING_SIZE];

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = CreateViewer();
  viewer->clearcolor = COLOR_DARKGRAY;
  MoveViewer(viewer, 0, 2, -4);
  TurnViewer(viewer, 15, 0, 0);

  /* load md2 */
  md2 = LoadObject("data/german.md2");
  md2->animmode = ANIM_LOOP;
  TurnObject(md2, 0, 90, 0);
  GetObjectMaterial(md2, 0)->texture = LoadTexture("data/german.png"); /* this shouldn't be necessary */

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    /* update animation */
    if (IsKeyPressed(KEY_SPACE))
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
    PrepareViewer(viewer);
    DrawObject(md2);

    /* draw ui */
    Setup2D();
    sprintf(str, "%i FPS", GetScreenFPS());
    DrawText(str, 4, 4);
    sprintf(str, "Frame: %i", (int)md2->animframe);
    DrawText(str, 4, 16);
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
