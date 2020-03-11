#include "../src/beam.h"
#include <stdio.h>

#define ROTATION_SPEED 90

int main() {
  /* Data */
  Viewer* viewer;
  Light* dir_light;
  Object* triangle;
  Material* material;
  char str[STRING_SIZE];

  /* Setup */
  bmInitBeam();
  bmSetScreen(800, 600, FALSE, TRUE);
  bmSetScreenTitle("Triangle");

  /* Create and position viewer */
  viewer = bmCreateViewer();
  bmSetViewerClearColor(viewer, COLOR_WHITE);
  bmSetViewerPosition(viewer, 0, 0, -2);

  /* Create a triangle */
  triangle = bmCreateTriangle();
  material = bmGetObjectMaterial(triangle, 0);
  bmSetMaterialFlags(material, bmGetMaterialFlags(material) - FLAG_CULL);
  bmSetMaterialDiffuse(material, COLOR_ORANGE);

  /* Main loop */
  while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
    bmTurnObject(triangle, 0, ROTATION_SPEED * bmGetDeltaTime(), 0);

    /* Draw scene */
    bmPrepareViewer(viewer);
    bmDrawObject(triangle);

    /* Draw UI */
    sprintf(str, "%i FPS", bmGetScreenFPS());
    bmSetup2D();
    bmDrawText(str, 4, 4);
    bmRefreshScreen();
  }

  /* Shutdown */
  bmShutdownBeam();
}
