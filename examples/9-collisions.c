#include "../src/beam.h"

int main()
{
  /* data */
  Object* floor;
  Object* ball;
  Object* block;
  Object* ball_shadow;
  Object* block_shadow;
  Viewer* viewer;
  Light* dir_light;
  int direction = 1;

  /* setup */
  InitBeam();
  SetScreen(800, 600, FALSE, TRUE);
  SetScreenTitle("Collisions");

  /* create floor */
  floor = CreateCube();
  MoveObject(floor, 0, -0.5f, 4);
  floor->colmode = COL_BOX;
  floor->sx = floor->sz = 20;
  GetObjectMaterial(floor, 0)->diffuse = COLOR_BLUE;

  /* load ball */
  ball = LoadObject("data/sphere.assbin");
  MoveObject(ball, 0, 0.5f, -4);
  ball->colmode = COL_SPHERE;
  ball->radius = 0.5f;
  GetObjectMaterial(ball, 0)->diffuse = COLOR_RED;

  /* create block */
  block = CreateCube();
  MoveObject(block, 0, 2, 0);
  block->colmode = COL_BOX;
  block->sx = block->sy = 4;
  GetObjectMaterial(block, 0)->diffuse = COLOR_LIGHTGRAY;

  /* create ball shadow */
  ball_shadow = CreateQuad();
  ball_shadow->pitch = 90;
  GetObjectMaterial(ball_shadow, 0)->texture = LoadTexture("data/circle_shadow.png");
  GetObjectMaterial(ball_shadow, 0)->diffuse = COLOR_BLACK;
  GetObjectMaterial(ball_shadow, 0)->blend = BLEND_ALPHA;

  /* create block shadow */
  block_shadow = CreateQuad();
  block_shadow->pitch = 90;
  block_shadow->sx = 4;
  GetObjectMaterial(block_shadow, 0)->diffuse = COLOR_LIGHTGRAY;
  GetObjectMaterial(block_shadow, 0)->blend = BLEND_MUL;

  /* create and position viewer */
  viewer = CreateViewer();
  MoveViewer(viewer, 0, 7, -8);
  TurnViewer(viewer, 45, 0, 0);

  /* setup lighting */
  SetAmbientColor(COLOR_LIGHTGRAY);
  dir_light = CreateLight(LIGHT_DIRECTIONAL);
  dir_light->pitch = 15;
  dir_light->yaw = 60;

  /* main loop */
  while (IsScreenOpened() && !IsKeyPressed(KEY_ESC))
  {
    /* move ball */
    if (IsKeyPressed(KEY_UP)) MoveObject(ball, 0, 0, 2 * GetDeltaTime());
    if (IsKeyPressed(KEY_DOWN)) MoveObject(ball, 0, 0, -2 * GetDeltaTime());
    if (IsKeyPressed(KEY_LEFT)) MoveObject(ball, -2 * GetDeltaTime(), 0, 0);
    if (IsKeyPressed(KEY_RIGHT)) MoveObject(ball, 2 * GetDeltaTime(), 0, 0);

    /* move block */
    MoveObject(block, 0, 2 * direction * GetDeltaTime(), 0);
    if (block->y >= 4)
    {
      block->y = 4;
      direction = -1;
    }
    if (ObjectCollidesObject(block, floor) || ObjectCollidesObject(block, ball))
    {
      direction = 1;
    }

    /* update shadows */
    ball_shadow->x = ball->x;
    ball_shadow->z = ball->z;
    block_shadow->x = block->x;
    block_shadow->z = block->z;

    /* draw scene */
    PrepareViewer(viewer);
    DrawObject(floor);
    DrawObject(ball);
    DrawObject(block);
    DrawObject(block_shadow);
    DrawObject(ball_shadow);

    /* draw ui */
    RefreshScreen();
  }

  /* shutdown */
  ShutdownBeam();
}
