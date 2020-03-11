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
  bmInitBeam();
  bmSetScreen(800, 600, FALSE, TRUE);
  bmSetScreenTitle("MD2 Animation");

  /* Create and position viewer */
  viewer = bmCreateViewer();
  bmSetViewerClearColor(viewer, COLOR_DARKGRAY);
  bmSetViewerPosition(viewer, 0, 2, -4);
  bmSetViewerRotation(viewer, 15, 0, 0);

  /* Load MD2 */
  md2 = bmLoadObject("data/german.md2");
  bmSetObjectAnimMode(md2, ANIM_LOOP);
  bmTurnObject(md2, 0, 90, 0);
  bmSetMaterialTexture(bmGetObjectMaterial(md2, 0), bmLoadTexture("data/german.png")); /* This shouldn't be necessary */

  /* Main loop */
  while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
    /* Update animation */
    if (bmIsKeyPressed(KEY_SPACE)) {
      if (!space_down) walking = !walking;
      space_down = TRUE;
    } else {
      space_down = FALSE;
    }
    if (walking) bmSetObjectAnimRange(md2, 31, 0); /* 51 */
    else bmSetObjectAnimRange(md2, 0, 25);

    /* Draw scene */
    bmPrepareViewer(viewer);
    bmDrawObject(md2);

    /* Draw UI */
    bmSetup2D();
    sprintf(str, "%i FPS", bmGetScreenFPS());
    bmDrawText(str, 4, 4);
    sprintf(str, "Frame: %i", bmGetObjectFrame(md2));
    bmDrawText(str, 4, 16);
    bmRefreshScreen();
  }

  /* Shutdown */
  bmShutdownBeam();
}
