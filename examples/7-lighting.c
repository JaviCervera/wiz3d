#include "../src/spark.h"
#include "../src/util.h"
#include <stdio.h>

#define NUM_LIGHTS_ 3
#define NUM_SPHERES 81
#define ROTATION_SPEED 32

int main() {
  /* Data */
  Viewer* viewer;
  Light* lights[NUM_LIGHTS_];
  Object* spheres[NUM_SPHERES];
  int x, z;
  int i;
  char str[STRING_SIZE];

  /* Setup */
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("Lighting");

  /* Create and position viewer */
  viewer = spCreateViewer();
  spSetViewerClearColor(viewer, COLOR_BLACK);
  spSetViewerPosition(viewer, 0, 32, -90);
  spSetViewerRotation(viewer, 16, 0, 0);

  /* Setup lighting */
  spSetAmbientColor(COLOR_BLACK);
  lights[0] = spCreateLight(LIGHT_POINT);
  spSetLightRange(lights[0], 192);
  spSetLightColor(lights[0], COLOR_RED);
  spSetLightRotation(lights[0], 0, 0);
  lights[1] = spCreateLight(LIGHT_POINT);
  spSetLightRange(lights[1], 192);
  spSetLightColor(lights[1], COLOR_GREEN);
  spSetLightRotation(lights[1], 0, 120);
  lights[2] = spCreateLight(LIGHT_POINT);
  spSetLightRange(lights[2], 192);
  spSetLightColor(lights[2], COLOR_BLUE);
  spSetLightRotation(lights[2], 0, 240);

  /* Create spheres */
  x = -32; z = -32;
  for (i = 0; i < NUM_SPHERES; ++i) {
    if (i == 0) {
      Material* material;
      spheres[i] = spLoadObject("data/sphere.assbin");
      spSetObjectScale(spheres[i], 4, 4, 4);
      material = spGetObjectMaterial(spheres[i], 0);
      spSetMaterialDiffuse(material, COLOR_WHITE);
      spSetMaterialSpecular(material, COLOR_WHITE);
      spSetMaterialShininess(material, 0.4f);
    } else {
      spheres[i] = spCloneObject(spheres[0]);
    }
    spSetObjectPosition(spheres[i], x, 0, z);
    x += 8;
    if (x > 32) {
      x = -32;
      z += 8;
    }
  }

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    /* Update lights */
    for (i = 0; i < NUM_LIGHTS_; ++i) {
      spTurnLight(lights[i], 0, -ROTATION_SPEED * spGetDeltaTime());
      spSetLightPosition(lights[i], 0, 0, 0);
      spMoveLight(lights[i], 0, 0, -48);
    }

    /* Draw scene */
    spPrepareViewer(viewer);
    for (i = 0; i < NUM_SPHERES; ++i) {
      spDrawObject(spheres[i]);
    }

    /* Draw UI */
    spSetup2D();
    sprintf(str, "%i FPS", spGetScreenFPS());
    spDrawText(str, 4, 4);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
