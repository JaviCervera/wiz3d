#include "../src/beam.h"
#include <stdio.h>

#define ROTATION_SPEED 90

int main()
{
  /* data */
  Viewer* viewer;
  Light* dir_light;
  Object* cube;
  char str[STRING_SIZE];

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = CreateViewer();
  viewer->clearcolor = GetRGB(15, 15, 15);
  MoveViewer(viewer, 0, 2, -2);
  ViewerLookAt(viewer, 0, 0, 0);

  /* setup lighting */
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  TurnLight(dir_light, 45, -45);

  /* create a cube */
  cube = CreateCube();
  GetObjectMaterial(cube, 0)->texture = LoadTexture("data/box.png");

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    TurnObject(cube, 0, ROTATION_SPEED * GetDeltaTime(), 0);

    /* draw scene */
    PrepareViewer(viewer);
    DrawObject(cube);

    /* draw ui */
    sprintf(str, "%i FPS", GetScreenFPS());
    Setup2D();
    DrawText(str, 4, 4);
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
