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
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Hoverbike");

  /* Create and position viewer */
  viewer = CreateViewer();
  SetViewerClearMode(viewer, CLEAR_SKYBOX);
  SetViewerSkybox(viewer, LoadTexture("data/skybox.png"));
  SetViewerPosition(viewer, 0, 4, -8);
  SetViewerRotation(viewer, 20, 0, 0);

  /* Setup lighting */
  SetDefaultShininessPower(2);
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  TurnLight(dir_light, 45, -45);

  /* Load hoverbike */
  hoverbike = LoadObject("data/hoverbike.assbin");
  SetObjectScale(hoverbike, 0.025f, 0.025f, 0.025f);
  mat0 = GetObjectMaterial(hoverbike, 0);
  mat1 = GetObjectMaterial(hoverbike, 1);
  SetMaterialTexture(mat0, LoadTexture("data/bike.png"));
  SetMaterialDiffuse(mat0, COLOR_WHITE);
  SetMaterialSpecular(mat0, COLOR_WHITE);
  SetMaterialTexture(mat1, LoadTexture("data/glass.png"));
  SetMaterialDiffuse(mat1, COLOR_WHITE);
  SetMaterialSpecular(mat1, COLOR_WHITE);
  SetMaterialBlend(mat1, BLEND_ALPHA);

  /* Main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    /* Turn hoverbike */
    TurnObject(hoverbike, 0, ROTATION_SPEED * GetDeltaTime(), 0);

    /* Draw scene */
    PrepareViewer(viewer);
    DrawObject(hoverbike);

    /* Draw UI */
    Setup2D();
    SetDrawColor(GetRGB(240, 240, 240));
    DrawText(TEXT, (GetScreenWidth() - GetTextWidth(TEXT)) / 2, 8);
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownBeam();
}
