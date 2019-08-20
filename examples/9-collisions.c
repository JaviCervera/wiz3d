#include "../src/spark.h"

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
  spInitSpark();
  spSetScreen(800, 600, FALSE, TRUE);
  spSetScreenTitle("Collisions");

  /* Create floor */
  floor = spCreateCube();
  spMoveObject(floor, 0, -0.5f, 4);
  spSetObjectCollision(floor, COL_BOX);
  spSetObjectScale(floor, 20, 1, 20);
  spSetMaterialDiffuse(spGetObjectMaterial(floor, 0), COLOR_BLUE);

  /* Load ball */
  ball = spLoadObject("data/sphere.assbin");
  spMoveObject(ball, 0, 0.5f, -4);
  spSetObjectCollision(ball, COL_SPHERE);
  spSetObjectRadius(ball, 0.5f);
  spSetMaterialDiffuse(spGetObjectMaterial(ball, 0), COLOR_RED);

  /* Create block */
  block = spCreateCube();
  spMoveObject(block, 0, 2, 0);
  spSetObjectCollision(block, COL_BOX);
  spSetObjectScale(block, 4, 4, 1);
  spSetMaterialDiffuse(spGetObjectMaterial(block, 0), COLOR_LIGHTGRAY);

  /* Create ball shadow */
  ball_shadow = spCreateQuad();
  spSetObjectRotation(ball_shadow, 90, 0, 0);
  spSetMaterialTexture(spGetObjectMaterial(ball_shadow, 0), spLoadTexture("data/circle_shadow.png"));
  spSetMaterialDiffuse(spGetObjectMaterial(ball_shadow, 0), COLOR_BLACK);
  spSetMaterialBlend(spGetObjectMaterial(ball_shadow, 0), BLEND_ALPHA);

  /* Create block shadow */
  block_shadow = spCreateQuad();
  spSetObjectRotation(block_shadow, 90, 0, 0);
  spSetObjectScale(block_shadow, 4, 1, 1);
  spSetMaterialDiffuse(spGetObjectMaterial(block_shadow, 0), COLOR_LIGHTGRAY);
  spSetMaterialBlend(spGetObjectMaterial(block_shadow, 0), BLEND_MUL);

  /* Create and position viewer */
  viewer = spCreateViewer();
  spMoveViewer(viewer, 0, 7, -8);
  spTurnViewer(viewer, 45, 0, 0);

  /* Setup lighting */
  spSetAmbientColor(COLOR_LIGHTGRAY);
  dir_light = spCreateLight(LIGHT_DIRECTIONAL);
  spSetLightRotation(dir_light, 15, 60);

  /* Main loop */
  while (spIsScreenOpened() && !spIsKeyPressed(KEY_ESC)) {
    /* Move ball */
    if (spIsKeyPressed(KEY_UP)) spMoveObject(ball, 0, 0, 2 * spGetDeltaTime());
    if (spIsKeyPressed(KEY_DOWN)) spMoveObject(ball, 0, 0, -2 * spGetDeltaTime());
    if (spIsKeyPressed(KEY_LEFT)) spMoveObject(ball, -2 * spGetDeltaTime(), 0, 0);
    if (spIsKeyPressed(KEY_RIGHT)) spMoveObject(ball, 2 * spGetDeltaTime(), 0, 0);

    /* Move block */
    spMoveObject(block, 0, 2 * direction * spGetDeltaTime(), 0);
    if (spGetObjectY(block) >= 4) {
      spSetObjectPosition(block, spGetObjectX(block), 4, spGetObjectZ(block));
      direction = -1;
    }
    if (spObjectCollidesObject(block, floor) || spObjectCollidesObject(block, ball)) {
      direction = 1;
    }

    /* Update shadows */
    spSetObjectPosition(ball_shadow, spGetObjectX(ball), 0, spGetObjectZ(ball));
    spSetObjectPosition(block_shadow, spGetObjectX(block), 0, spGetObjectZ(block));

    /* Draw scene */
    spPrepareViewer(viewer);
    spDrawObject(floor);
    spDrawObject(ball);
    spDrawObject(block);
    spDrawObject(block_shadow);
    spDrawObject(ball_shadow);

    /* Draw UI */
    spRefreshScreen();
  }

  /* Shutdown */
  spShutdownSpark();
}
