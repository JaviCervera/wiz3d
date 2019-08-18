#include "../src/beam.h"
#include <math.h>

#define ROTATION_SPEED 32
#define TEXT "Frank by misterdevious is licensed under CC Attribution-NonCommercial-ShareAlike"

int main() {
  /* Data */
  Viewer* viewer;
  Light* dir_light;
  Light* point_light1;
  Light* point_light2;
  Object* angel;
  float value = 0;

  /* Setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Angel");

  /* Create and position viewer */
  viewer = CreateViewer();
  SetViewerClearColor(viewer, GetRGB(15, 15, 15));
  SetViewerPosition(viewer, 7, 7, -7);
  ViewerLookAt(viewer, 0, 0, 0);

  /* Setup lighting */
  SetAmbientColor(GetRGB(15, 15, 15));
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  SetLightColor(dir_light, GetRGB(100, 100, 100));
  point_light1 = CreateLight(LIGHT_POINT);
  SetLightPosition(point_light1, 0, 0, -2);
  SetLightColor(point_light1, GetRGB(255, 100, 0));
  point_light2 = CreateLight(LIGHT_POINT);
  SetLightPosition(point_light2, 0, 8, 4);
  SetLightColor(point_light2, GetRGB(0, 100, 255));

  /* Load object (contains embedded texture) */
  angel = LoadObject("data/angel.assbin");
  TurnObject(angel, 90, 0, 0);

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    float s, c;

    /* Rotate statue */
    TurnObject(angel, 0, ROTATION_SPEED * GetDeltaTime(), 0);

    /* Update lighting */
    value += GetDeltaTime();
    s = 0.5f + fabsf(sinf(value)) * 0.5f;
    c = 0.5f + fabsf(cosf(value)) * 0.5f;
    SetLightRange(point_light1, 10 * s);
    SetLightRange(point_light2, 10 * c);

    /* Draw scene */
    PrepareViewer(viewer);
    DrawObject(angel);

    /* Draw UI */
    Setup2D();
    SetDrawColor(GetRGB(240, 240, 240));
    DrawText(TEXT, (GetScreenWidth() - GetTextWidth(TEXT)) / 2, 8);
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownBeam();
}
