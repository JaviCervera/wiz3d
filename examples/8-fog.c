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
  InitSpark();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Fog");

  /* Setup lighting */
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  TurnLight(dir_light, 45, 45);

  /* Create and position viewer */
  viewer = CreateViewer();
  SetViewerClearColor(viewer, COLOR_DARKGRAY);
  SetViewerPosition(viewer, 0, 0, -7);
  SetViewerDistance(viewer, 1, 5000);
  SetViewerFogEnabled(viewer, TRUE);
  SetViewerFogDistance(viewer, 0, 20);

  /* Create billboards */
  x = -7;
  z = NUM_CUBES / 16 * 2 - 2;
  for (i = 0; i < NUM_CUBES; i += 2) {
    Object* cube;

    if (i == 0) {
      cube = CreateCube();
      SetMaterialDiffuse(GetObjectMaterial(cube, 0), COLOR_BROWN);
    } else {
      cube = CloneObject(cubes[0]);
    }
    SetObjectPosition(cube, x, -1.5f, z);
    cubes[i] = cube;

    cube = CloneObject(cubes[0]);
    SetObjectPosition(cube, x, 1.5f, z);
    cubes[i+1] = cube;
    
    x += 2;
    if (x > 7) {
      x = -7;
      z -= 2;
    }
  }

  /* Main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    /* Turn objects */
    for (i = 0; i < NUM_CUBES; ++i) {
      TurnObject(cubes[i], 0, ROTATION_SPEED * GetDeltaTime(), 0);
    }

    /* Draw scene */
    PrepareViewer(viewer);
    for (i = 0; i < NUM_CUBES; ++i) {
      DrawObject(cubes[i]);
    }

    /* Draw UI */
    sprintf(str, "%i FPS", GetScreenFPS());
    Setup2D();
    DrawText(str, 4, 4);
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownSpark();
}
