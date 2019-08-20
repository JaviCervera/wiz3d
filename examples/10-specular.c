#include "../src/spark.h"
#include "../src/util.h"
#include <stdio.h>

int main() {
  /* Data */
  Viewer* viewer;
  Light* dir_light;
  Object* cube;
  Material* mat;
  char str[STRING_SIZE];

  /* Setup */
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("Specular");

  /* Create and position viewer */
  viewer = spCreateViewer();
  spSetViewerClearColor(viewer, COLOR_DARKGRAY);
  spSetViewerPosition(viewer, 0, 0, -6);

  /* Setup lighting */
  dir_light = spCreateLight(LIGHT_DIRECTIONAL);
  spTurnLight(dir_light, 30, 20);

  /* Create a cube */
  cube = spCreateCube();
  mat = spGetObjectMaterial(cube, 0);
  spTurnObject(cube, 45, 45, 0);
  spSetMaterialDiffuse(mat, COLOR_ORANGE);
  spSetMaterialShininess(mat, 0);

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    /* Update shininess */
    if (spIsKeyPressed(KEY_LEFT)) spSetMaterialShininess(mat, _Clamp(spGetMaterialShininess(mat) - 0.2f * spGetDeltaTime(), 0, 1));
    if (spIsKeyPressed(KEY_RIGHT)) spSetMaterialShininess(mat, _Clamp(spGetMaterialShininess(mat) + 0.2f * spGetDeltaTime(), 0, 1));

    /* Draw scene */
    spPrepareViewer(viewer);
    spDrawObject(cube);

    /* Draw ui */
    spSetup2D();
    sprintf(str, "%i FPS", spGetScreenFPS());
    spDrawText(str, 4, 4);
    sprintf(str, "Shininess: %f (LEFT and RIGHT to change)", spGetMaterialShininess(mat));
    spDrawText(str, 4, 16);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
