#include "../src/beam.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_BILLBOARDS 64
#define ROTATION_SPEED 32

int main() {
  /* Data */
  Viewer* viewer;
  Texture* tex;
  Object* billboards[NUM_BILLBOARDS];
  int x, z;
  int i;
  char str[STRING_SIZE];

  /* Setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Billboards");

  /* Create and position viewer */
  viewer = CreateViewer();
  SetViewerClearColor(viewer, COLOR_WHITE);
  SetViewerRotation(viewer, 45, -45, 0);

  /* Load texture */
  tex = LoadTexture("data/smile.png");

  /* Create billboards */
  x = z = -8;
  for (i = 0; i < NUM_BILLBOARDS; ++i) {
    Material* material;

    billboards[i] = CreateQuad();
    SetObjectPosition(billboards[i], x, 0, z);
    material = GetObjectMaterial(billboards[i], 0);
    SetMaterialTexture(material, tex);
    SetMaterialDiffuse(material, GetRGB(rand() % 256, rand() % 256, rand() % 256));
    SetMaterialBlend(material, BLEND_ALPHA);
    
    x += 2;
    if (x >= 8) {
      x = -8;
      z += 2;
    }
  }

  /* Main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    /* Update viewer */
    TurnViewer(viewer, 0, ROTATION_SPEED * GetDeltaTime(), 0);
    SetViewerPosition(viewer, 0, 0, 0);
    MoveViewer(viewer, 0, 0, -8);

    /* Update billboards */
    for (i = 0; i < NUM_BILLBOARDS; ++i) {
      ObjectLookAt(billboards[i], GetViewerX(viewer), GetViewerY(viewer), GetViewerZ(viewer));
    }

    /* Draw scene */
    PrepareViewer(viewer);
    for (i = 0; i < NUM_BILLBOARDS; ++i) {
      DrawObject(billboards[i]);
    }

    /* Draw UI */
    sprintf(str, "%i FPS", GetScreenFPS());
    Setup2D();
    SetDrawColor(COLOR_BLACK);
    DrawText(str, 4, 4);
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownBeam();
}
