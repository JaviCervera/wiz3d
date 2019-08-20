#include "../src/spark.h"
#include <stdio.h>

#define ROTATION_SPEED 90

int main() {
  /* Data */
  Viewer* viewer;
  Light* dir_light;
  Object* triangle;
  Material* material;
  char str[STRING_SIZE];

  /* Setup */
  InitSpark();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Triangle");

  /* Create and position viewer */
  viewer = CreateViewer();
  SetViewerClearColor(viewer, COLOR_WHITE);
  SetViewerPosition(viewer, 0, 0, -2);

  /* Create a triangle */
  triangle = CreateTriangle();
  material = GetObjectMaterial(triangle, 0);
  SetMaterialFlags(material, GetMaterialFlags(material) - FLAG_CULL);
  SetMaterialDiffuse(material, COLOR_ORANGE);

  /* Main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    TurnObject(triangle, 0, ROTATION_SPEED * GetDeltaTime(), 0);

    /* Draw scene */
    PrepareViewer(viewer);
    DrawObject(triangle);

    /* Draw UI */
    sprintf(str, "%i FPS", GetScreenFPS());
    Setup2D();
    DrawText(str, 4, 4);
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownSpark();
}
