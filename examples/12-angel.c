#include "../src/spark.h"
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
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("Angel");

  /* Create and position viewer */
  viewer = spCreateViewer();
  spSetViewerClearColor(viewer, spGetRGB(15, 15, 15));
  spSetViewerPosition(viewer, 7, 7, -7);
  spViewerLookAt(viewer, 0, 0, 0);

  /* Setup lighting */
  spSetAmbientColor(spGetRGB(15, 15, 15));
  dir_light = spCreateLight(LIGHT_DIRECTIONAL);
  spSetLightColor(dir_light, spGetRGB(100, 100, 100));
  point_light1 = spCreateLight(LIGHT_POINT);
  spSetLightPosition(point_light1, 0, 0, -2);
  spSetLightColor(point_light1, spGetRGB(255, 100, 0));
  point_light2 = spCreateLight(LIGHT_POINT);
  spSetLightPosition(point_light2, 0, 8, 4);
  spSetLightColor(point_light2, spGetRGB(0, 100, 255));

  /* Load object (contains embedded texture) */
  angel = spLoadObject("data/angel.assbin");
  spTurnObject(angel, 90, 0, 0);

  /* main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    float s, c;

    /* Rotate statue */
    spTurnObject(angel, 0, ROTATION_SPEED * spGetDeltaTime(), 0);

    /* Update lighting */
    value += spGetDeltaTime();
    s = 0.5f + fabsf(sinf(value)) * 0.5f;
    c = 0.5f + fabsf(cosf(value)) * 0.5f;
    spSetLightRange(point_light1, 10 * s);
    spSetLightRange(point_light2, 10 * c);

    /* Draw scene */
    spPrepareViewer(viewer);
    spDrawObject(angel);

    /* Draw UI */
    spSetup2D();
    spSetDrawColor(spGetRGB(240, 240, 240));
    spDrawText(TEXT, (spGetScreenWidth() - spGetTextWidth(TEXT)) / 2, 8);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
