#include "../src/spark.h"
#include <stdio.h>

#define ROTATION_SPEED 90

int main() {
  /* data */
  Viewer* viewer;
  Light* dir_light;
  Object* cube;
  char str[STRING_SIZE];

  /* Setup */
  InitSpark();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Rotating Cube");

  /* Create and position viewer */
  viewer = CreateViewer();
  SetViewerClearColor(viewer, GetRGB(15, 15, 15));
  SetViewerPosition(viewer, 0, 2, -2);
  ViewerLookAt(viewer, 0, 0, 0);

  /* Setup lighting */
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  TurnLight(dir_light, 45, -45);

  /* Create a cube */
  cube = CreateCube();
  SetMaterialTexture(GetObjectMaterial(cube, 0), LoadTexture("data/box.png"));

  /* Main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    TurnObject(cube, 0, ROTATION_SPEED * GetDeltaTime(), 0);

    /* Draw scene */
    PrepareViewer(viewer);
    DrawObject(cube);

    /* Draw UI */
    sprintf(str, "%i FPS", GetScreenFPS());
    Setup2D();
    DrawText(str, 4, 4);
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownSpark();
}
