#include "../src/beam.h"

#define ROTATION_SPEED 32
#define TEXT "Hover Bike by Ptis is licensed under CC Attribution-NonCommercial"

int main() {
  /* Data */
  Viewer* viewer;
  Light* dir_light;
  Object* hoverbike;
  Material* mat0;
  Material* mat1;

  /* Setup */
  bmInitBeam();
  bmSetScreen(800, 600, FALSE, TRUE);
  bmSetScreenTitle("Hoverbike");

  /* Create and position viewer */
  viewer = bmCreateViewer();
  bmSetViewerClearMode(viewer, CLEAR_SKYBOX);
  bmSetViewerSkybox(viewer, bmLoadTexture("data/skybox.png"));
  bmSetViewerPosition(viewer, 0, 4, -8);
  bmSetViewerRotation(viewer, 20, 0, 0);

  /* Setup lighting */
  dir_light = bmCreateLight(LIGHT_DIRECTIONAL);
  bmTurnLight(dir_light, 45, -45);

  /* Load hoverbike */
  hoverbike = bmLoadObject("data/hoverbike.assbin");
  bmSetObjectScale(hoverbike, 0.025f, 0.025f, 0.025f);
  mat0 = bmGetObjectMaterial(hoverbike, 0);
  mat1 = bmGetObjectMaterial(hoverbike, 1);
  bmSetMaterialTexture(mat0, bmLoadTexture("data/bike.png"));
  bmSetMaterialDiffuse(mat0, COLOR_WHITE);
  bmSetMaterialSpecular(mat0, COLOR_WHITE);
  bmSetMaterialShininess(mat0, 0.8f);
  bmSetMaterialTexture(mat1, bmLoadTexture("data/glass.png"));
  bmSetMaterialDiffuse(mat1, COLOR_WHITE);
  bmSetMaterialSpecular(mat1, COLOR_WHITE);
  bmSetMaterialShininess(mat1, 0.8f);
  bmSetMaterialBlend(mat1, BLEND_ALPHA);

  /* Main loop */
  while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
    /* Turn hoverbike */
    bmTurnObject(hoverbike, 0, ROTATION_SPEED * bmGetDeltaTime(), 0);

    /* Draw scene */
    bmPrepareViewer(viewer);
    bmDrawObject(hoverbike);

    /* Draw UI */
    bmSetup2D();
    bmSetDrawColor(bmGetRGB(240, 240, 240));
    bmDrawText(TEXT, (bmGetScreenWidth() - bmGetTextWidth(TEXT)) / 2, 8);
    bmRefreshScreen();
  }

  /* Shutdown */
  bmShutdownBeam();
}
