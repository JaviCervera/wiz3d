#include "../src/spark.h"
#include <stdio.h>

int main() {
  /* Data */
  Viewer* viewer;
  Object* md2;
  bool_t walking;
  bool_t space_down;
  char str[STRING_SIZE];

  /* Setup */
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("MD2 Animation");

  /* Create and position viewer */
  viewer = spCreateViewer();
  spSetViewerClearColor(viewer, COLOR_DARKGRAY);
  spSetViewerPosition(viewer, 0, 2, -4);
  spSetViewerRotation(viewer, 15, 0, 0);

  /* Load MD2 */
  md2 = spLoadObject("data/german.md2");
  spSetObjectAnimMode(md2, ANIM_LOOP);
  spTurnObject(md2, 0, 90, 0);
  spSetMaterialTexture(spGetObjectMaterial(md2, 0), spLoadTexture("data/german.png")); /* This shouldn't be necessary */

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    /* Update animation */
    if (spIsKeyPressed(KEY_SPACE)) {
      if (!space_down) walking = !walking;
      space_down = TRUE;
    } else {
      space_down = FALSE;
    }
    if (walking) spSetObjectAnimRange(md2, 31, 0); /* 51 */
    else spSetObjectAnimRange(md2, 0, 25);

    /* Draw scene */
    spPrepareViewer(viewer);
    spDrawObject(md2);

    /* Draw UI */
    spSetup2D();
    sprintf(str, "%i FPS", spGetScreenFPS());
    spDrawText(str, 4, 4);
    sprintf(str, "Frame: %i", spGetObjectFrame(md2));
    spDrawText(str, 4, 16);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
