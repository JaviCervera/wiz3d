#include "../src/beam.h"
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
  bmInitBeam();
  bmSetScreen(800, 600, FALSE, TRUE);
  bmSetScreenTitle("Lightmapping");

  /* Create and position viewer */
  viewer = bmCreateViewer();
  bmSetViewerClearColor(viewer, bmGetRGB(15, 15, 15));
  bmSetViewerPosition(viewer, 0, 2, -2);
  bmViewerLookAt(viewer, 0, 0, 0);

  /* Setup lighting */
  bmSetAmbientColor(COLOR_BLACK);
  dir_light = bmCreateLight(LIGHT_DIRECTIONAL);
  bmTurnLight(dir_light, 45, -45);

  /* Create a cube */
  cube = bmCreateCube();
  material = bmGetObjectMaterial(cube, 0);
  bmSetMaterialTexture(material, bmLoadTexture("data/box.png"));
  bmSetMaterialLightmap(material, bmLoadTexture("data/lightmap.png"));

  /* Main loop */
  while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
    /* Update lighting mode */
    if (bmIsKeyPressed(KEY_SPACE)) {
      if (!space_down) {
        if (bmGetMaterialFlags(material) & FLAG_LIGHTING) {
          bmSetMaterialFlags(material, bmGetMaterialFlags(material) - FLAG_LIGHTING);
        } else {
          bmSetMaterialFlags(material, bmGetMaterialFlags(material) + FLAG_LIGHTING);
        }
      }
      space_down = TRUE;
    } else {
      space_down = FALSE;
    }

    /* Turn cube */
    bmTurnObject(cube, 0, ROTATION_SPEED * bmGetDeltaTime(), 0);

    /* Draw scene */
    bmPrepareViewer(viewer);
    bmDrawObject(cube);

    /* Draw UI */
    bmSetup2D();
    sprintf(str, "%i FPS", bmGetScreenFPS());
    bmDrawText(str, 4, 4);
    sprintf(str, "Press SPACE to switch dynamic lighting");
    bmDrawText(str, 4, 16);
    bmRefreshScreen();
  }

  /* Shutdown */
  bmShutdownBeam();
}
