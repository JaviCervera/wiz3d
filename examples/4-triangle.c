#include "../src/spark.h"
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
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("Triangle");

  /* Create and position viewer */
  viewer = spCreateViewer();
  spSetViewerClearColor(viewer, COLOR_WHITE);
  spSetViewerPosition(viewer, 0, 0, -2);

  /* Create a triangle */
  triangle = spCreateTriangle();
  material = spGetObjectMaterial(triangle, 0);
  spSetMaterialFlags(material, spGetMaterialFlags(material) - FLAG_CULL);
  spSetMaterialDiffuse(material, COLOR_ORANGE);

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    spTurnObject(triangle, 0, ROTATION_SPEED * spGetDeltaTime(), 0);

    /* Draw scene */
    spPrepareViewer(viewer);
    spDrawObject(triangle);

    /* Draw UI */
    sprintf(str, "%i FPS", spGetScreenFPS());
    spSetup2D();
    spDrawText(str, 4, 4);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
