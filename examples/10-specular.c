#include "../src/beam.h"
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
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Specular");

  /* Create and position viewer */
  viewer = CreateViewer();
  SetViewerClearColor(viewer, COLOR_DARKGRAY);
  SetViewerPosition(viewer, 0, 0, -6);

  /* Setup lighting */
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  TurnLight(dir_light, 30, 20);

  /* Create a cube */
  cube = CreateCube();
  mat = GetObjectMaterial(cube, 0);
  TurnObject(cube, 45, 45, 0);
  SetMaterialDiffuse(mat, COLOR_ORANGE);
  SetMaterialShininess(mat, 0);

  /* Main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    /* Update shininess */
    if (IsKeyPressed(KEY_LEFT)) SetMaterialShininess(mat, _Clamp(GetMaterialShininess(mat) - 0.2f * GetDeltaTime(), 0, 1));
    if (IsKeyPressed(KEY_RIGHT)) SetMaterialShininess(mat, _Clamp(GetMaterialShininess(mat) + 0.2f * GetDeltaTime(), 0, 1));

    /* Draw scene */
    PrepareViewer(viewer);
    DrawObject(cube);

    /* Draw ui */
    Setup2D();
    sprintf(str, "%i FPS", GetScreenFPS());
    DrawText(str, 4, 4);
    sprintf(str, "Shininess: %f (LEFT and RIGHT to change)", GetMaterialShininess(mat));
    DrawText(str, 4, 16);
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownBeam();
}
