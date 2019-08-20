#include "../src/spark.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_CUBES (16 * 50)
#define ROTATION_SPEED 32

int main() {
  /* Data */
  Light* dir_light;
  Viewer* viewer;
  Object* cubes[NUM_CUBES];
  int x, z;
  int i;
  char str[STRING_SIZE];

  /* Setup */
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("Fog");

  /* Setup lighting */
  dir_light = spCreateLight(LIGHT_DIRECTIONAL);
  spTurnLight(dir_light, 45, 45);

  /* Create and position viewer */
  viewer = spCreateViewer();
  spSetViewerClearColor(viewer, COLOR_DARKGRAY);
  spSetViewerPosition(viewer, 0, 0, -7);
  spSetViewerDistance(viewer, 1, 5000);
  spSetViewerFogEnabled(viewer, TRUE);
  spSetViewerFogDistance(viewer, 0, 20);

  /* Create billboards */
  x = -7;
  z = NUM_CUBES / 16 * 2 - 2;
  for (i = 0; i < NUM_CUBES; i += 2) {
    Object* cube;

    if (i == 0) {
      cube = spCreateCube();
      spSetMaterialDiffuse(spGetObjectMaterial(cube, 0), COLOR_BROWN);
    } else {
      cube = spCloneObject(cubes[0]);
    }
    spSetObjectPosition(cube, x, -1.5f, z);
    cubes[i] = cube;

    cube = spCloneObject(cubes[0]);
    spSetObjectPosition(cube, x, 1.5f, z);
    cubes[i+1] = cube;
    
    x += 2;
    if (x > 7) {
      x = -7;
      z -= 2;
    }
  }

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    /* Turn objects */
    for (i = 0; i < NUM_CUBES; ++i) {
      spTurnObject(cubes[i], 0, ROTATION_SPEED * spGetDeltaTime(), 0);
    }

    /* Draw scene */
    spPrepareViewer(viewer);
    for (i = 0; i < NUM_CUBES; ++i) {
      spDrawObject(cubes[i]);
    }

    /* Draw UI */
    sprintf(str, "%i FPS", spGetScreenFPS());
    spSetup2D();
    spDrawText(str, 4, 4);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
