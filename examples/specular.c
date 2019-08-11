#include "../src/beam.h"
#include "../src/util.h"
#include <stdio.h>

int main()
{
  /* data */
  Viewer* viewer;
  Light* dir_light;
  Object* cube;
  Material* mat;
  char str[STRING_SIZE];

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = CreateViewer();
  viewer->clearcolor = COLOR_DARKGRAY;
  MoveViewer(viewer, 0, 0, -6);

  /* setup lighting */
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  TurnLight(dir_light, 30, 20);

  /* create a cube */
  cube = CreateCube();
  mat = GetObjectMaterial(cube, 0);
  TurnObject(cube, 45, 45, 0);
  mat->diffuse = COLOR_ORANGE;
  mat->shininess = 0;

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    /* update shininess */
    if (IsKeyPressed(KEY_LEFT)) mat->shininess = _Clamp(mat->shininess - 0.2f * GetDeltaTime(), 0, 1);
    if (IsKeyPressed(KEY_RIGHT)) mat->shininess = _Clamp(mat->shininess + 0.2f * GetDeltaTime(), 0, 1);

    /* draw scene */
    PrepareViewer(viewer);
    DrawObject(cube);

    /* draw ui */
    Setup2D();
    sprintf(str, "%i FPS", GetScreenFPS());
    DrawText(str, 4, 4);
    sprintf(str, "Shininess: %f (LEFT and RIGHT to change)", mat->shininess);
    DrawText(str, 4, 16);
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
