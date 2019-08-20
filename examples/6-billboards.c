#include "../src/spark.h"
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
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("Billboards");

  /* Create and position viewer */
  viewer = spCreateViewer();
  spSetViewerClearColor(viewer, COLOR_WHITE);
  spSetViewerRotation(viewer, 45, -45, 0);

  /* Load texture */
  tex = spLoadTexture("data/smile.png");

  /* Create billboards */
  x = z = -8;
  for (i = 0; i < NUM_BILLBOARDS; ++i) {
    Material* material;

    billboards[i] = spCreateQuad();
    spSetObjectPosition(billboards[i], x, 0, z);
    material = spGetObjectMaterial(billboards[i], 0);
    spSetMaterialTexture(material, tex);
    spSetMaterialDiffuse(material, spGetRGB(rand() % 256, rand() % 256, rand() % 256));
    spSetMaterialBlend(material, BLEND_ALPHA);
    
    x += 2;
    if (x >= 8) {
      x = -8;
      z += 2;
    }
  }

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    /* Update viewer */
    spTurnViewer(viewer, 0, ROTATION_SPEED * spGetDeltaTime(), 0);
    spSetViewerPosition(viewer, 0, 0, 0);
    spMoveViewer(viewer, 0, 0, -8);

    /* Update billboards */
    for (i = 0; i < NUM_BILLBOARDS; ++i) {
      spObjectLookAt(billboards[i], spGetViewerX(viewer), spGetViewerY(viewer), spGetViewerZ(viewer));
    }

    /* Draw scene */
    spPrepareViewer(viewer);
    for (i = 0; i < NUM_BILLBOARDS; ++i) {
      spDrawObject(billboards[i]);
    }

    /* Draw UI */
    sprintf(str, "%i FPS", spGetScreenFPS());
    spSetup2D();
    spSetDrawColor(COLOR_BLACK);
    spDrawText(str, 4, 4);
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
