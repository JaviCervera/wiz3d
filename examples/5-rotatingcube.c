#include "../src/spark.h"
#include <stdio.h>

#define ROTATION_SPEED 90

int main() {
  /* Data */
  Viewer* viewer;
  Light* dir_light;
  Object* cube;
  char str[STRING_SIZE];

  /* Setup */
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("Rotating Cube");

  /* Create and position viewer */
  viewer = spCreateViewer();
  spSetViewerClearColor(viewer, spGetRGB(15, 15, 15));
  spSetViewerPosition(viewer, 0, 2, -2);
  spViewerLookAt(viewer, 0, 0, 0);

  /* Setup lighting */
  dir_light = spCreateLight(LIGHT_DIRECTIONAL);
  spTurnLight(dir_light, 45, -45);

  /* Create a cube */
  cube = spCreateCube();
  spSetMaterialTexture(spGetObjectMaterial(cube, 0), spLoadTexture("data/box.png"));

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    spTurnObject(cube, 0, ROTATION_SPEED * spGetDeltaTime(), 0);

    /* Draw scene */
    spPrepareViewer(viewer);
    spDrawObject(cube);

    /* Draw UI */
    sprintf(str, "%i FPS", spGetScreenFPS());
    spSetup2D();
    spDrawText(str, 4, 4);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
