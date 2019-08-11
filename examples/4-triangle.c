#include "../src/beam.h"
#include <stdio.h>

#define ROTATION_SPEED 90

int main()
{
  /* data */
  Viewer* viewer;
  Light* dir_light;
  Object* triangle;
  char str[STRING_SIZE];

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Triangle");

  /* create and position viewer */
  viewer = CreateViewer();
  viewer->clearcolor = COLOR_WHITE;
  MoveViewer(viewer, 0, 0, -2);

  /* create a triangle */
  triangle = CreateTriangle();
  GetObjectMaterial(triangle, 0)->flags -= FLAG_CULL;
  GetObjectMaterial(triangle, 0)->diffuse = COLOR_ORANGE;

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    TurnObject(triangle, 0, ROTATION_SPEED * GetDeltaTime(), 0);

    /* draw scene */
    PrepareViewer(viewer);
    DrawObject(triangle);

    /* draw ui */
    sprintf(str, "%i FPS", GetScreenFPS());
    Setup2D();
    DrawText(str, 4, 4);
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
