#include "../src/beam.h"
#include <stdio.h>

int main() {
  /* Data */
  Viewer* viewer;
  Object* md2;
  bool_t walking;
  bool_t space_down;
  char str[STRING_SIZE];

  /* Setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("MD2 Animation");

  /* Create and position viewer */
  viewer = CreateViewer();
  SetViewerClearColor(viewer, COLOR_DARKGRAY);
  SetViewerPosition(viewer, 0, 2, -4);
  SetViewerRotation(viewer, 15, 0, 0);

  /* Load MD2 */
  md2 = LoadObject("data/german.md2");
  SetObjectAnimMode(md2, ANIM_LOOP);
  TurnObject(md2, 0, 90, 0);
  SetMaterialTexture(GetObjectMaterial(md2, 0), LoadTexture("data/german.png")); /* This shouldn't be necessary */

  /* Main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    /* Update animation */
    if (IsKeyPressed(KEY_SPACE)) {
      if (!space_down) walking = !walking;
      space_down = TRUE;
    } else {
      space_down = FALSE;
    }
    if (walking) SetObjectAnimRange(md2, 31, 0); /* 51 */
    else SetObjectAnimRange(md2, 0, 25);

    /* Draw scene */
    PrepareViewer(viewer);
    DrawObject(md2);

    /* Draw UI */
    Setup2D();
    sprintf(str, "%i FPS", GetScreenFPS());
    DrawText(str, 4, 4);
    sprintf(str, "Frame: %i", GetObjectFrame(md2));
    DrawText(str, 4, 16);
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownBeam();
}
