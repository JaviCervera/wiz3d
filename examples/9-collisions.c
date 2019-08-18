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
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Collisions");

  /* Create floor */
  floor = CreateCube();
  MoveObject(floor, 0, -0.5f, 4);
  SetObjectCollision(floor, COL_BOX);
  SetObjectScale(floor, 20, 1, 20);
  SetMaterialDiffuse(GetObjectMaterial(floor, 0), COLOR_BLUE);

  /* Load ball */
  ball = LoadObject("data/sphere.assbin");
  MoveObject(ball, 0, 0.5f, -4);
  SetObjectCollision(ball, COL_SPHERE);
  SetObjectRadius(ball, 0.5f);
  SetMaterialDiffuse(GetObjectMaterial(ball, 0), COLOR_RED);

  /* Create block */
  block = CreateCube();
  MoveObject(block, 0, 2, 0);
  SetObjectCollision(block, COL_BOX);
  SetObjectScale(block, 4, 4, 1);
  SetMaterialDiffuse(GetObjectMaterial(block, 0), COLOR_LIGHTGRAY);

  /* Create ball shadow */
  ball_shadow = CreateQuad();
  SetObjectRotation(ball_shadow, 90, 0, 0);
  SetMaterialTexture(GetObjectMaterial(ball_shadow, 0), LoadTexture("data/circle_shadow.png"));
  SetMaterialDiffuse(GetObjectMaterial(ball_shadow, 0), COLOR_BLACK);
  SetMaterialBlend(GetObjectMaterial(ball_shadow, 0), BLEND_ALPHA);

  /* Create block shadow */
  block_shadow = CreateQuad();
  SetObjectRotation(block_shadow, 90, 0, 0);
  SetObjectScale(block_shadow, 4, 1, 1);
  SetMaterialDiffuse(GetObjectMaterial(block_shadow, 0), COLOR_LIGHTGRAY);
  SetMaterialBlend(GetObjectMaterial(block_shadow, 0), BLEND_MUL);

  /* Create and position viewer */
  viewer = CreateViewer();
  MoveViewer(viewer, 0, 7, -8);
  TurnViewer(viewer, 45, 0, 0);

  /* Setup lighting */
  SetAmbientColor(COLOR_LIGHTGRAY);
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  SetLightRotation(dir_light, 15, 60);

  /* Main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC)) {
    /* Move ball */
    if (IsKeyPressed(KEY_UP)) MoveObject(ball, 0, 0, 2 * GetDeltaTime());
    if (IsKeyPressed(KEY_DOWN)) MoveObject(ball, 0, 0, -2 * GetDeltaTime());
    if (IsKeyPressed(KEY_LEFT)) MoveObject(ball, -2 * GetDeltaTime(), 0, 0);
    if (IsKeyPressed(KEY_RIGHT)) MoveObject(ball, 2 * GetDeltaTime(), 0, 0);

    /* Move block */
    MoveObject(block, 0, 2 * direction * GetDeltaTime(), 0);
    if (GetObjectY(block) >= 4) {
      SetObjectPosition(block, GetObjectX(block), 4, GetObjectZ(block));
      direction = -1;
    }
    if (ObjectCollidesObject(block, floor) || ObjectCollidesObject(block, ball)) {
      direction = 1;
    }

    /* Update shadows */
    SetObjectPosition(ball_shadow, GetObjectX(ball), 0, GetObjectZ(ball));
    SetObjectPosition(block_shadow, GetObjectX(block), 0, GetObjectZ(block));

    /* Draw scene */
    PrepareViewer(viewer);
    DrawObject(floor);
    DrawObject(ball);
    DrawObject(block);
    DrawObject(block_shadow);
    DrawObject(ball_shadow);

    /* Draw UI */
    RefreshScreen();
  }

  /* Shutdown */
  ShutdownBeam();
}
