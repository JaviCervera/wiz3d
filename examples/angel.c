#include "../src/beam.h"
#include <math.h>

#define ROTATION_SPEED 32
#define TEXT "Frank by misterdevious is licensed under CC Attribution-NonCommercial-ShareAlike"

int main()
{
  /* data */
  Viewer* viewer;
  Light* dir_light;
  Light* point_light1;
  Light* point_light2;
  Object* angel;
  float value = 0;

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);

  /* create and position viewer */
  viewer = CreateViewer();
  viewer->clearcolor = GetRGB(15, 15, 15);
  MoveViewer(viewer, 7, 7, -7);
  TurnViewer(viewer, 37.5f, -45, 0);

  /* setup lighting */
  SetAmbientColor(GetRGB(15, 15, 15));
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  dir_light->color = GetRGB(100, 100, 100);
  point_light1 = CreateLight(LIGHT_POINT);
  MoveLight(point_light1, 0, 0, -2);
  point_light1->color = GetRGB(255, 100, 0);
  point_light2 = CreateLight(LIGHT_POINT);
  MoveLight(point_light2, 0, 8, 4);
  point_light2->color = GetRGB(0, 100, 255);

  /* load object (contains embedded texture) */
  angel = LoadObject("data/angel.assbin");
  TurnObject(angel, 90, 0, 0);

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    float s, c;

    /* rotate statue */
    TurnObject(angel, 0, ROTATION_SPEED * GetDeltaTime(), 0);

    /* update lighting */
    value += GetDeltaTime();
    s = 0.5f + fabsf(sinf(value)) * 0.5f;
    c = 0.5f + fabsf(cosf(value)) * 0.5f;
    point_light1->range = 10 * s;
    point_light2->range = 10 * c;

    /* draw scene */
    PrepareViewer(viewer);
    DrawObject(angel);

    /* draw ui */
    Setup2D();
    SetDrawColor(GetRGB(240, 240, 240));
    DrawText(TEXT, (GetScreenWidth() - GetTextWidth(TEXT)) / 2, 8);
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
