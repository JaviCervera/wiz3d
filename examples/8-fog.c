#include "../src/beam.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_CUBES (16 * 50)
#define ROTATION_SPEED 32

int main()
{
  /* data */
  Light* dir_light;
  Viewer* viewer;
  Object* cubes[NUM_CUBES];
  int x, z;
  int i;
  char str[STRING_SIZE];

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Fog");

  /* setup lighting */
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  TurnLight(dir_light, 45, 45);

  /* create and position viewer */
  viewer = CreateViewer();
  viewer->clearcolor = COLOR_DARKGRAY;
  MoveViewer(viewer, 0, 0, -7);
  viewer->max = 5000;
  viewer->fogenabled = TRUE;
  viewer->fogmax = 20;

  /* create billboards */
  x = -7;
  z = NUM_CUBES / 16 * 2 - 2;
  for (i = 0; i < NUM_CUBES; i += 2)
  {
    Object* cube;

    if (i == 0)
    {
      cube = CreateCube();
      GetObjectMaterial(cube, 0)->diffuse = COLOR_BROWN;
    }
    else
    {
      cube = CloneObject(cubes[0]);
    }
    cube->x = x;
    cube->y = -1.5f;
    cube->z = z;
    cubes[i] = cube;

    cube = CloneObject(cubes[0]);
    cube->x = x;
    cube->y = 1.5f;
    cube->z = z;
    cubes[i+1] = cube;
    
    x += 2;
    if (x > 7)
    {
      x = -7;
      z -= 2;
    }
  }

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    /* turn objects */
    for (i = 0; i < NUM_CUBES; ++i)
    {
      TurnObject(cubes[i], 0, ROTATION_SPEED * GetDeltaTime(), 0);
    }

    /* draw scene */
    PrepareViewer(viewer);
    for (i = 0; i < NUM_CUBES; ++i)
    {
      DrawObject(cubes[i]);
    }

    /* draw ui */
    sprintf(str, "%i FPS", GetScreenFPS());
    Setup2D();
    DrawText(str, 4, 4);
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
