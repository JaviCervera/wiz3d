#include "../src/beam.h"
#include "../src/util.h"
#include <stdio.h>

#define NUM_LIGHTS_ 3
#define NUM_SPHERES 81
#define ROTATION_SPEED 32

int main() {
  /* Data */
  Viewer* viewer;
  Light* lights[NUM_LIGHTS_];
  Object* spheres[NUM_SPHERES];
  int x, z;
  int i;
  char str[STRING_SIZE];

  /* Setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Lighting");

  /* Create and position viewer */
  viewer = CreateViewer();
  SetViewerClearColor(viewer, COLOR_BLACK);
  SetViewerPosition(viewer, 0, 32, -90);
  SetViewerRotation(viewer, 16, 0, 0);

  /* Setup lighting */
  SetAmbientColor(COLOR_BLACK);
  lights[0] = CreateLight(LIGHT_POINT);
  SetLightRange(lights[0], 192);
  SetLightColor(lights[0], COLOR_RED);
  SetLightRotation(lights[0], 0, 0);
  lights[1] = CreateLight(LIGHT_POINT);
  SetLightRange(lights[1], 192);
  SetLightColor(lights[1], COLOR_GREEN);
  SetLightRotation(lights[1], 0, 120);
  lights[2] = CreateLight(LIGHT_POINT);
  SetLightRange(lights[2], 192);
  SetLightColor(lights[2], COLOR_BLUE);
  SetLightRotation(lights[2], 0, 240);

  /* Create spheres */
  x = -32; z = -32;
  for (i = 0; i < NUM_SPHERES; ++i) {
    if (i == 0) {
      Material* material;
      spheres[i] = LoadObject("data/sphere.assbin");
      SetObjectScale(spheres[i], 4, 4, 4);
      material = GetObjectMaterial(spheres[i], 0);
      SetMaterialDiffuse(material, COLOR_WHITE);
      SetMaterialSpecular(material, COLOR_WHITE);
      SetMaterialShininess(material, 0.4f);
    } else {
      spheres[i] = CloneObject(spheres[0]);
    }
    SetObjectPosition(spheres[i], x, 0, z);
    x += 8;
    if (x > 32) {
      x = -32;
      z += 8;
    }
  }

  /* Main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    /* Update lights */
    for (i = 0; i < NUM_LIGHTS_; ++i) {
      TurnLight(lights[i], 0, -ROTATION_SPEED * GetDeltaTime());
      SetLightPosition(lights[i], 0, 0, 0);
      MoveLight(lights[i], 0, 0, -48);
    }

    /* Draw scene */
    PrepareViewer(viewer);
    for (i = 0; i < NUM_SPHERES; ++i) {
      DrawObject(spheres[i]);
    }

    /* Draw UI */
    Setup2D();
    sprintf(str, "%i FPS", GetScreenFPS());
    DrawText(str, 4, 4);
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownBeam();
}
