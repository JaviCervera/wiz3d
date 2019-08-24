#include "../src/spark.h"
#include <stdio.h>

#define ROTATION_SPEED 90

int main() {
  /* Data */
  Viewer* viewer;
  Light* dir_light;
  Object* cube;
  Material* material;
  bool_t space_down;
  char str[STRING_SIZE];

  /* Setup */
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("Lightmapping");

  /* Create and position viewer */
  viewer = spCreateViewer();
  spSetViewerClearColor(viewer, spGetRGB(15, 15, 15));
  spSetViewerPosition(viewer, 0, 2, -2);
  spViewerLookAt(viewer, 0, 0, 0);

  /* Setup lighting */
  spSetAmbientColor(COLOR_BLACK);
  dir_light = spCreateLight(LIGHT_DIRECTIONAL);
  spTurnLight(dir_light, 45, -45);

  /* Create a cube */
  cube = spCreateCube();
  material = spGetObjectMaterial(cube, 0);
  spSetMaterialTexture(material, spLoadTexture("data/box.png"));
  spSetMaterialLightmap(material, spLoadTexture("data/lightmap.png"));

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    /* Update lighting mode */
    if (spIsKeyPressed(KEY_SPACE)) {
      if (!space_down) {
        if (spGetMaterialFlags(material) & FLAG_LIGHTING) {
          spSetMaterialFlags(material, spGetMaterialFlags(material) - FLAG_LIGHTING);
        } else {
          spSetMaterialFlags(material, spGetMaterialFlags(material) + FLAG_LIGHTING);
        }
      }
      space_down = TRUE;
    } else {
      space_down = FALSE;
    }

    /* Turn cube */
    spTurnObject(cube, 0, ROTATION_SPEED * spGetDeltaTime(), 0);

    /* Draw scene */
    spPrepareViewer(viewer);
    spDrawObject(cube);

    /* Draw UI */
    spSetup2D();
    sprintf(str, "%i FPS", spGetScreenFPS());
    spDrawText(str, 4, 4);
    sprintf(str, "Press SPACE to switch dynamic lighting");
    spDrawText(str, 4, 16);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
