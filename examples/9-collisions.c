#include "../src/beam.h"

int main() {
  /* Data */
  Object* floor;
  Object* ball;
  Object* block;
  Object* ball_shadow;
  Object* block_shadow;
  Viewer* viewer;
  Light* dir_light;
  int direction = 1;

  /* Setup */
  bmInitBeam();
  bmSetScreen(800, 600, FALSE, TRUE);
  bmSetScreenTitle("Collisions");

  /* Create floor */
  floor = bmCreateCube();
  bmMoveObject(floor, 0, -0.5f, 4);
  bmSetObjectCollision(floor, COL_BOX);
  bmSetObjectScale(floor, 20, 1, 20);
  bmSetMaterialDiffuse(bmGetObjectMaterial(floor, 0), COLOR_BLUE);

  /* Load ball */
  ball = bmLoadObject("data/sphere.assbin");
  bmMoveObject(ball, 0, 0.5f, -4);
  bmSetObjectCollision(ball, COL_SPHERE);
  bmSetObjectRadius(ball, 0.5f);
  bmSetMaterialDiffuse(bmGetObjectMaterial(ball, 0), COLOR_RED);

  /* Create block */
  block = bmCreateCube();
  bmMoveObject(block, 0, 2, 0);
  bmSetObjectCollision(block, COL_BOX);
  bmSetObjectScale(block, 4, 4, 1);
  bmSetMaterialDiffuse(bmGetObjectMaterial(block, 0), COLOR_LIGHTGRAY);

  /* Create ball shadow */
  ball_shadow = bmCreateQuad();
  bmSetObjectRotation(ball_shadow, 90, 0, 0);
  bmSetMaterialTexture(bmGetObjectMaterial(ball_shadow, 0), bmLoadTexture("data/circle_shadow.png"));
  bmSetMaterialDiffuse(bmGetObjectMaterial(ball_shadow, 0), COLOR_BLACK);
  bmSetMaterialBlend(bmGetObjectMaterial(ball_shadow, 0), BLEND_ALPHA);

  /* Create block shadow */
  block_shadow = bmCreateQuad();
  bmSetObjectRotation(block_shadow, 90, 0, 0);
  bmSetObjectScale(block_shadow, 4, 1, 1);
  bmSetMaterialDiffuse(bmGetObjectMaterial(block_shadow, 0), COLOR_LIGHTGRAY);
  bmSetMaterialBlend(bmGetObjectMaterial(block_shadow, 0), BLEND_MUL);

  /* Create and position viewer */
  viewer = bmCreateViewer();
  bmMoveViewer(viewer, 0, 7, -8);
  bmTurnViewer(viewer, 45, 0, 0);

  /* Setup lighting */
  bmSetAmbientColor(COLOR_LIGHTGRAY);
  dir_light = bmCreateLight(LIGHT_DIRECTIONAL);
  bmSetLightRotation(dir_light, 15, 60);

  /* Main loop */
  while (bmIsScreenOpened() && !bmIsKeyPressed(KEY_ESC)) {
    /* Move ball */
    if (bmIsKeyPressed(KEY_UP)) bmMoveObject(ball, 0, 0, 2 * bmGetDeltaTime());
    if (bmIsKeyPressed(KEY_DOWN)) bmMoveObject(ball, 0, 0, -2 * bmGetDeltaTime());
    if (bmIsKeyPressed(KEY_LEFT)) bmMoveObject(ball, -2 * bmGetDeltaTime(), 0, 0);
    if (bmIsKeyPressed(KEY_RIGHT)) bmMoveObject(ball, 2 * bmGetDeltaTime(), 0, 0);

    /* Move block */
    bmMoveObject(block, 0, 2 * direction * bmGetDeltaTime(), 0);
    if (bmGetObjectY(block) >= 4) {
      bmSetObjectPosition(block, bmGetObjectX(block), 4, bmGetObjectZ(block));
      direction = -1;
    }
    if (bmObjectCollidesObject(block, floor) || bmObjectCollidesObject(block, ball)) {
      direction = 1;
    }

    /* Update shadows */
    bmSetObjectPosition(ball_shadow, bmGetObjectX(ball), 0, bmGetObjectZ(ball));
    bmSetObjectPosition(block_shadow, bmGetObjectX(block), 0, bmGetObjectZ(block));

    /* Draw scene */
    bmPrepareViewer(viewer);
    bmDrawObject(floor);
    bmDrawObject(ball);
    bmDrawObject(block);
    bmDrawObject(block_shadow);
    bmDrawObject(ball_shadow);

    /* Draw UI */
    bmRefreshScreen();
  }

  /* Shutdown */
  bmShutdownBeam();
}
