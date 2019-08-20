#include "../src/spark.h"

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
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("Hoverbike");

  /* Create and position viewer */
  viewer = spCreateViewer();
  spSetViewerClearMode(viewer, CLEAR_SKYBOX);
  spSetViewerSkybox(viewer, spLoadTexture("data/skybox.png"));
  spSetViewerPosition(viewer, 0, 4, -8);
  spSetViewerRotation(viewer, 20, 0, 0);

  /* Setup lighting */
  spSetDefaultShininessPower(2);
  dir_light = spCreateLight(LIGHT_DIRECTIONAL);
  spTurnLight(dir_light, 45, -45);

  /* Load hoverbike */
  hoverbike = spLoadObject("data/hoverbike.assbin");
  spSetObjectScale(hoverbike, 0.025f, 0.025f, 0.025f);
  mat0 = spGetObjectMaterial(hoverbike, 0);
  mat1 = spGetObjectMaterial(hoverbike, 1);
  spSetMaterialTexture(mat0, spLoadTexture("data/bike.png"));
  spSetMaterialDiffuse(mat0, COLOR_WHITE);
  spSetMaterialSpecular(mat0, COLOR_WHITE);
  spSetMaterialTexture(mat1, spLoadTexture("data/glass.png"));
  spSetMaterialDiffuse(mat1, COLOR_WHITE);
  spSetMaterialSpecular(mat1, COLOR_WHITE);
  spSetMaterialBlend(mat1, BLEND_ALPHA);

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    /* Turn hoverbike */
    spTurnObject(hoverbike, 0, ROTATION_SPEED * spGetDeltaTime(), 0);

    /* Draw scene */
    spPrepareViewer(viewer);
    spDrawObject(hoverbike);

    /* Draw UI */
    spSetup2D();
    spSetDrawColor(spGetRGB(240, 240, 240));
    spDrawText(TEXT, (spGetScreenWidth() - spGetTextWidth(TEXT)) / 2, 8);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
