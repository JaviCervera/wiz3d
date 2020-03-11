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
  bmInitBeam();
  bmSetScreen(800, 600, FALSE, TRUE);
  bmSetScreenTitle("Billboards");

  /* Create and position viewer */
  viewer = bmCreateViewer();
  bmSetViewerClearColor(viewer, COLOR_WHITE);
  bmSetViewerRotation(viewer, 45, -45, 0);

  /* Load texture */
  tex = bmLoadTexture("data/smile.png");

  /* Create billboards */
  x = z = -8;
  for (i = 0; i < NUM_BILLBOARDS; ++i) {
    Material* material;

    billboards[i] = bmCreateQuad();
    bmSetObjectPosition(billboards[i], x, 0, z);
    material = bmGetObjectMaterial(billboards[i], 0);
    bmSetMaterialTexture(material, tex);
    bmSetMaterialDiffuse(material, bmGetRGB(rand() % 256, rand() % 256, rand() % 256));
    bmSetMaterialBlend(material, BLEND_ALPHA);
    
    x += 2;
    if (x >= 8) {
      x = -8;
      z += 2;
    }
  }

  /* Main loop */
  while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
    /* Update viewer */
    bmTurnViewer(viewer, 0, ROTATION_SPEED * bmGetDeltaTime(), 0);
    bmSetViewerPosition(viewer, 0, 0, 0);
    bmMoveViewer(viewer, 0, 0, -8);

    /* Update billboards */
    for (i = 0; i < NUM_BILLBOARDS; ++i) {
      bmObjectLookAt(billboards[i], bmGetViewerX(viewer), bmGetViewerY(viewer), bmGetViewerZ(viewer));
    }

    /* Draw scene */
    bmPrepareViewer(viewer);
    for (i = 0; i < NUM_BILLBOARDS; ++i) {
      bmDrawObject(billboards[i]);
    }

    /* Draw UI */
    sprintf(str, "%i FPS", bmGetScreenFPS());
    bmSetup2D();
    bmSetDrawColor(COLOR_BLACK);
    bmDrawText(str, 4, 4);
    bmRefreshScreen();
  }

  /* Shutdown */
  bmShutdownBeam();
}
