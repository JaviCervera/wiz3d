#include "../src/beam.h"
#include "../src/util.h"
#include <stdio.h>

#define NUM_LIGHTS_ 3
#define NUM_SPHERES 81
#define ROTATION_SPEED 32

int main()
{
  /* data */
  Viewer* viewer;
  Light* lights[NUM_LIGHTS_];
  Object* spheres[NUM_SPHERES];
  int x, z;
  int i;
  char str[STRING_SIZE];

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Lighting");

  /* create and position viewer */
  viewer = CreateViewer();
  viewer->clearcolor = COLOR_BLACK;
  MoveViewer(viewer, 0, 32, -90);
  TurnViewer(viewer, 16, 0, 0);

  /* setup lighting */
  SetAmbientColor(COLOR_BLACK);
  lights[0] = CreateLight(LIGHT_POINT);
  lights[0]->range = 192;
  lights[0]->color = COLOR_RED;
  lights[0]->yaw = 0;
  lights[1] = CreateLight(LIGHT_POINT);
  lights[1]->range = 192;
  lights[1]->color = COLOR_GREEN;
  lights[1]->yaw = 120;
  lights[2] = CreateLight(LIGHT_POINT);
  lights[2]->range = 192;
  lights[2]->color = COLOR_BLUE;
  lights[2]->yaw = 240;

  /* create spheres */
  x = -32; z = -32;
  for (i = 0; i < NUM_SPHERES; ++i) {
    if (i == 0) {
      spheres[i] = LoadObject("data/sphere.assbin");
      spheres[i]->sx = spheres[i]->sy = spheres[i]->sz = 4;
      GetObjectMaterial(spheres[i], 0)->diffuse = COLOR_WHITE;
      GetObjectMaterial(spheres[i], 0)->specular = COLOR_WHITE;
      GetObjectMaterial(spheres[i], 0)->shininess = 0.4f;
    } else {
      spheres[i] = CloneObject(spheres[0]);
    }
    spheres[i]->x = x;
    spheres[i]->z = z;
    x += 8;
    if (x > 32) {
      x = -32;
      z += 8;
    }
  }

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    /* update lights */
    for (i = 0; i < NUM_LIGHTS_; ++i) {
      lights[i]->yaw -= ROTATION_SPEED * GetDeltaTime();
      lights[i]->x = lights[i]->y = lights[i]->z = 0;
      MoveLight(lights[i], 0, 0, -48);
    }

    /* draw scene */
    PrepareViewer(viewer);
    for (i = 0; i < NUM_SPHERES; ++i) {
      DrawObject(spheres[i]);
    }

    /* draw ui */
    Setup2D();
    sprintf(str, "%i FPS", GetScreenFPS());
    DrawText(str, 4, 4);
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
